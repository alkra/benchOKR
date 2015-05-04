/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce Point contient l'implémentation des méthodes de la classe Octree. */

#include "../include/Octree.h"
#include<cstring>

Octree::Octree():  m_pointCount(0), m_points(NULL), m_centre(0,0,0,0), m_rayon(0.0)
{
    memset(m_enfant, 0, sizeof(m_enfant));
}


Octree::~Octree()
{
    delete[] m_points;
}



// construction de l'Octree

const   bool    Octree::build(Point **points,
                              const unsigned int count,

                              const unsigned int threshold,
                              const unsigned int maximumDepth,
                              const Bounds &bounds,
                              const unsigned int currentDepth)
{

    if (count <= threshold || currentDepth >= maximumDepth)
    {
        // Just store the points in the node, making it a leaf
// on doit travailler avec les éléments de la classe fichier
        m_pointCount = count;
        m_points = new Point *[count];
        memcpy(m_points, points, sizeof(Point *) * count);
        return true;
    }

    unsigned int    childPointCounts[8];

    // Affecter chaque point à un octant
    for (unsigned int i = 0; i < count; i++)
    {
        //  p est le point courant

        Point   &p = *points[i];

        // c: centre du noeud courant

        const Point &c = bounds.centre;

        // Here, we need to know which child each point belongs to. To
        // do this, we build an index into the _child[] array using the
        // relative position of the point to the centre of the current
        // node

        p.code=0;
        if (p.getX() > c.getX()) p.code |= 1;
        if (p.getY() > c.getY()) p.code |= 2;
        if (p.getZ() > c.getZ()) p.code |= 4;

        // We'll need to keep track of how many points get stuck in each
        // child so we'll just keep track of it here, since we have the
        // information handy.

        childPointCounts[p.code]++;
    }

    // Recursively call build() for each of the 8 children

    for (int i = 0; i < 8; i++)
    {
        // Don't bother going any further if there aren't any points for
        // this child

        if (!childPointCounts[i]) continue;

        // Allocate the child

        m_enfant[i] = new Octree;  // il faut créer un noeudOctree

        // Allocate a list of points that were coded JUST for this child
        // only

        Point   **newList = new Point *[childPointCounts[i]];

        // Go through the input list of points and copy over the points
        // that were coded for this child

        Point   **ptr = newList;

        for (unsigned int j = 0; j < count; j++)
        {
            if (points[j]->code == i)
            {
                *ptr = points[j];
                ptr++;
            }
        }

        // At this point, we have a list of points that will belong to
        // this child node. We'll want to remove any point with a
        // duplicate 'n' in them...
        //
        // [We won't need to reallocate the list, since it's temporary]

        int     newCount = 0;
        for (int j = 0; j < childPointCounts[i]; j++)
        {
            // Remove duplicates from newList
            // ...
            // Keep track of the new count in 'newCount'
        }

        // Generate a new bounding volume -- We do this with a touch of
        // trickery...
        //
        // We use a table of offsets. These offsets determine where a
        // node is, relative to it's parent. So, for example, if want to
        // generate the bottom-left-rear (-x, -y, -z) child for a node,
        // we use (-1, -1, -1).
        //
        // However, since the rayon of a child is always half of its
        // parent's, we use a table of 0.5, rather than 1.0.
        //
        // These values are stored the following table. Note that this
        // won't compile because it assumes Points are structs, but you
        // get the idea.

        Point   boundsOffsetTable[8] =
        {
            {-0.5, -0.5, -0.5},
            {+0.5, -0.5, -0.5},
            {-0.5, +0.5, -0.5},
            {+0.5, +0.5, -0.5},
            {-0.5, -0.5, +0.5},
            {+0.5, -0.5, +0.5},
            {-0.5, +0.5, +0.5},
            {+0.5, +0.5, +0.5}
        };

        // Calculate our offset from the centre of the parent's node to
        // the centre of the child's node

        Point   offset = boundsOffsetTable[i] * bounds.rayon;

        // Create a new Bounds, with the centre offset and half the
        // rayon

        Bounds  newBounds;
        newBounds.rayon = bounds.rayon * 0.5;
        newBounds.centre = bounds.centre + offset;

        // Recurse

        m_enfant[i]->construire(newList, newCount, threshold, maximumDepth,
                         newBounds, currentDepth+1);

        // Clean up

        delete[] newList;
    }
    return true;
}

// calcul du voulume englobant

const Bounds Octree::calcCubicBounds(const Point * const * points,
                                     const unsigned int count)
{
    // What we'll give to the caller

    Bounds  b;

    // Determine min/max of the given set of points

    Point   min = *points[0];
    Point   max = *points[0];

    for (unsigned int i = 1; i < count; i++)
    {
        const Point &p = *points[i];
        if (p.getX() < min.getX()) min.setX(p.getX());
        if (p.getY() < min.getY()) min.setY(p.getY());
        if (p.getZ() < min.getZ()) min.setZ(p.getZ());
        if (p.getX() > max.getX()) max.setX(p.getX());
        if (p.getY() > max.getY()) max.setY(p.getY());
        if (p.getZ() > max.getZ()) max.setZ(p.getZ());
    }


    Point   rayon = max - min;


    b.centre = min + rayon * 0.5;

    // We want a CUBIC space. By this, I mean we want a bounding cube, not
    // just a bounding box. We already have the centre, we just need a
    // rayon that contains the entire volume. To do this, we find the
    // maxumum value of the rayon' X/Y/Z components and use that

    b.rayon = rayon.getX();
    if (b.rayon < rayon.getY()) b.rayon = rayon.getY();
    if (b.rayon < rayon.getZ()) b.rayon = rayon.getZ();

    // Done

    return b;
}

const bool Octree::traverse(callback proc, void *data) const
{
    // Call the callback for this node (if the callback returns false, then
    // stop traversing.

    if (!proc(*this, data)) return false;

    // If I'm a node, recursively traverse my children

    if (!_pointCount)
    {
        for (unsigned int i = 0; i < 8; i++)
        {
            // We store incomplete trees (i.e. we're not guaranteed
            // that a node has all 8 children)

            if (!_child[i]) continue;

            if (!_child[i]->traverse(proc, data)) return false;
        }
    }

    return true;
}





QVector<Point> Octree::requete(const Point &centre, double distance) const {
    // requête sur un voisinage
}

QVector<Point> Octree::requete(const Voxel &conteneur) const {
    // requête dans un voxel
}

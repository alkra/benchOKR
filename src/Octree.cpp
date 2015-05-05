/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce Point contient l'implémentation des méthodes de la classe Octree. */

#include "../include/Octree.h"
#include<cstring>

Octree::Octree(): m_centre(0,0,0,0), m_rayon(0.0)
{

}


Octree::~Octree()
{
}



// construction de l'Octree

const   bool    Octree::construire(QString adresse,

                              const unsigned int threshold,
                              const unsigned int maximumDepth,
                              const Bounds &bounds,
                              const unsigned int currentDepth)
{
    Fichier plyInitial;
    if(!plyInitial.ouvrir(adresse, QIODevice::ReadOnly | QIODevice::Text)) {
        cerr << "Impossible d'ouvrir le ply initial " << adresse.toStdString() << endl;
        return false;
    }

    Point ** points = plyInitial.getPoints();
    const unsigned int count = plyInitial.getNbPoints();

    return racine->construire(points, count, threshold, maximumDepth, bounds, currentDepth);
}

// calcul du voulume englobant

const Bounds Octree::calcCubicBounds(const Point * const * points,
                                     const unsigned int count)
{


    Bounds  b;

    // Détermination du minimum et du maximum de notre jeu de données


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

    // Ici, nous voulons un espace cublique. Pour cela, nous avons besoin d'un volume englobant, autrement dit un cube
    // de sélection. Nous connaissons déja le centre, nous aurons juste besoin du rayon qui contient tout le volume
    // Pour réaliser cela, noous trouvons le maximum du rayon suivant les composantes X,Y et Z


    b.rayon = rayon.getX();
    if (b.rayon < rayon.getY()) b.rayon = rayon.getY();
    if (b.rayon < rayon.getZ()) b.rayon = rayon.getZ();

    // Done

    return b;
}

//const bool Octree::traverse(callback proc, void *data) const
//{
//    // Call the callback for this node (if the callback returns false, then
//    // stop traversing.

//    if (!proc(*this, data)) return false;

//    // If I'm a node, recursively traverse my children

//    if (!_pointCount)
//    {
//        for (unsigned int i = 0; i < 8; i++)
//        {
//            // We store incomplete trees (i.e. we're not guaranteed
//            // that a node has all 8 children)

//            if (!_child[i]) continue;

//            if (!_child[i]->traverse(proc, data)) return false;
//        }
//    }

//    return true;
//}





QVector<Point> Octree::requete(const Point &centre, double distance) const {
    // requête sur un voisinage
}

QVector<Point> Octree::requete(const Voxel &conteneur) const {
    // requête dans un voxel
}

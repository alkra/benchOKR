/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe NoeudOctree
 */

#include "../include/NoeudOctree.h"
#include "../include/Point.h"
#include <QDebug>
#include<string>

using namespace std;

NoeudOctree::NoeudOctree() :  m_pointCount(0), m_points(NULL), Noeud() {
   // memset(m_enfant, 0, sizeof(m_enfant));

}

NoeudOctree::~NoeudOctree()
{
    delete[] m_points;
}

const   bool    NoeudOctree::construire(Point** points,
                                        unsigned int count,
                                        const unsigned int threshold,
                                        const unsigned int maximumDepth,
                                        const Bounds &bounds,
                                        std::string relation,
                                        const unsigned int currentDepth)
{
    Point   &pt0 = *points[0]; // recuperation du premier point de la liste

    //if (count <= threshold)// || (currentDepth >= maximumDepth))
    if (currentDepth >= maximumDepth)
    {


        // pour le stockage des points dans les noeuds si les conditions sont remplies, ce qui fait de ce noeud une feuille.
     cout << "Fin --> relation " << relation << " grille numero " <<pt0.m_code << " profondeur " << currentDepth << " nombre de points " <<  count << endl;
       //qDebug() << "relation" << relation << "grille n°" <std::toString(pt0.m_code) << "profondeur " << currentDepth << "nombre de points " <<  count;
     relation="";



        //m_pointCount = count;
        //m_points = new Point *[count];
        //memcpy(m_points, points, sizeof(Point *) * count);
        return true;
    }

    unsigned int    childPointCounts[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    // Pendant cette étape, on va affecter chaque point à un noeud (octant)
    for (unsigned int i = 0; i < count; i++)
    {
        //  p est le point courant

        Point   &p = *points[i];

        // c: centre du noeud courant

        const Point &c = bounds.centre;



        // Ici, on doit connaître, à quel octant affecter un point.
        // Pour réaliser cela, on construit un index dans le tableau des octants en utilisant la position relative
        // du point au centre du noeud courant

        p.m_code=0;
        if (p.getX() > c.getX()) {
            p.m_code |= 1;
        }
        if (p.getY() > c.getY()) {
            p.m_code |= 2;
        }
        if (p.getZ() > c.getZ()) {
            p.m_code |= 4;
        }

        // On allons garder les informations concernant le nombre de points dans chaque octant


        childPointCounts[p.m_code]++;
    }

    // On appelle de recursivement la méthode construire pour chacun des 8 octants
    NoeudOctree                  *m_enfant[8];

    for (unsigned int i = 0; i < 8; i++)
    {
        // On arrête s'il n'y a pas de point dans un octant concerné


        if (!childPointCounts[i]) continue;

        // On affecte maintenant les octants et alloue une liste de points pour l'octant concerné seulement


        m_enfant[i] = new NoeudOctree();

       // qDebug() << childPointCounts[i];
        Point   **newList = NULL;
        newList = new Point *[childPointCounts[i]];

        // Go through the input list of points and copy over the points
        // that were coded for this child

        // On parcourt la liste des points d'entrée et la liste des points et et le stocke dans l'octant
        Point   **ptr = newList;

        for (unsigned int j = 0; j < count; j++)
        {
            if (points[j]->m_code == i)
            {
                *ptr = points[j];
                ptr++;
            }
        }

        // A ce niveau, nous avons une liste de points qui appartiennent à ce noeud enfant


        //        int     newCount = 0;
        //        for (unsigned int j = 0; j < childPointCounts[i]; j++)
        //        {

        //        }

        //Générer un volume englobant
        // Nous utilisons une table de décallage.
        //Ces décalages de déterminer où un noeud est, par rapport à son parent.


        Point   boundsOffsetTable[8] =
        {
            Point(-0.5, -0.5, -0.5),
            Point(+0.5, -0.5, -0.5),
            Point(-0.5, +0.5, -0.5),
            Point(+0.5, +0.5, -0.5),
            Point(-0.5, -0.5, +0.5),
            Point(+0.5, -0.5, +0.5),
            Point(-0.5, +0.5, +0.5),
            Point(+0.5, +0.5, +0.5)
        };


        // Calcul de notre décallage issu du centre du noeud parent au centre du noeud enfant


        Point   offset = boundsOffsetTable[i] * bounds.rayon;

        // création d'un nouveau volume englobant avec le centre du décallage
        // et la moitié du rayon

        Bounds  newBounds;
        newBounds.rayon = bounds.rayon * 0.5;
        newBounds.centre = bounds.centre + offset;

        // Recurse
        // pour le stockage des points dans les noeuds si les conditions sont remplies, ce qui fait de ce noeud une feuille.
        //qDebug() << "grille n°" << p.m_code

        std::string temp = relation +  "." + std::to_string(pt0.m_code);
        //relation += "." + std::to_string(pt0.m_code);
        cout << "Debut --> relation " << temp << " grille numero " << pt0.m_code << " profondeur " << currentDepth << " nombre de points " <<  count << endl;

         // test de recherche de source de plantage code
        if ((count ==44525) && (currentDepth==2)){


            cout << "Stop";
        }
        m_enfant[i]->construire(newList, childPointCounts[i], threshold, maximumDepth,
                                newBounds,temp, currentDepth+1 );

        // Tout nettoyer

        delete[] newList;
    }
    return true;
}



/* Les fonctions de requête */
QVector<Point> NoeudOctree::requete(const Point &centre, double distance) const {
    // renvoie tous les points de tous les enfants se trouvant dans le voisinage
}

QVector<Point> NoeudOctree::requete(const Voxel &conteneur) const {
}

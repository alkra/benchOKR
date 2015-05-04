#ifndef OCTREE_H
#define OCTREE_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce Point définit la classe Octree */

#include "../include/Arbre.h"
#include "NoeudOctree.h"
#include "Point.h"

typedef struct  // on déclare ici une structure pour stocker le volume englobant
{
    Point           centre;         // Centre du volume englobant
    double          rayon;         // Rayon du volume eglobant
} Bounds;



class Octree : public Arbre<NoeudOctree>  // Création d'une classe Octree qui hérite de la classe Arbre
{

public:

    // fonction de rappel pour la création des Points

    typedef bool            (*callback)(const Octree &o, void *data);

   // constructeur

    Octree();

    // destructeur
    virtual ~Octree();
    // méthode permettant de construire l'octree

    virtual const   bool            construire(Point **points, // on récupère la liste des points
                                               const unsigned int count,   // nombre total de points
                                               const unsigned int threshold, // seuil d'arrêt
                                               const unsigned int maximumDepth, // profondeur de l'arbre
                                               const Bounds &bounds,            // volume englobant
                                               const unsigned int currentDepth = 0); // profondeur courante

    // méthode permettant de construire le volume englobant

    static  const   Bounds          calcCubicBounds(const Point * const * points,  // correspond  liste dans la classe Point
                                                    const unsigned int count);

    // définition de la fonction qui sera rappelée pour la création des Points

    virtual const   bool            traverse(callback proc, void *data) const;

    // fonction de requête

    QVector<Point> requete(const Point &centre, double distance) const; // voisinage
    QVector<Point> requete(const Voxel &conteneur) const; // dans un voxel

protected:

    Octree                  *m_enfant[8]; // tableau du nombre d'octant
    unsigned int            m_pointCount; // nombre de points
    Point                   **m_points;
    Point                   m_centre;
    double                 m_rayon;
private:
};

#endif // OCTREE_H

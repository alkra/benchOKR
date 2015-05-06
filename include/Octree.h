#ifndef OCTREE_H
#define OCTREE_H

/* �ENSG 2015
 * �cole nationale des sciences g�ographiques
 * 6-8 avenue Blaise Pascal
 * Cit� Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALL�E CEDEX 2
 * FRANCE */

/* Ce Point d�finit la classe Octree */

#include "../include/Arbre.h"
#include "../include/NoeudOctree.h"
#include "Point.h"

using namespace std;




class Octree : public Arbre<NoeudOctree>  // Cr�ation d'une classe Octree qui h�rite de la classe Arbre
{

public:

    // fonction de rappel pour la cr�ation des Points

   // typedef bool            (*callback)(const Octree &o, void *data);

   // constructeur

    Octree();

    // destructeur
     ~Octree();
    // m�thode permettant de construire l'octree
    void construire();

     const   bool            construire(QString adresse,   // nombre total de points
                                               const unsigned int threshold, // seuil d'arr�t
                                               const unsigned int maximumDepth, // profondeur de l'arbre           // volume englobant
                                               const unsigned int currentDepth = 0); // profondeur courante

    // m�thode permettant de construire le volume englobant

    static  const   Bounds          calcCubicBounds(const Point * const * points,
                                                    const unsigned int count);



    // d�finition de la fonction qui sera rappel�e pour la cr�ation des Points

    //  virtual const   bool            traverse(callback proc, void *data) const;

    // fonction de requ�te

    QVector<Point> requete(const Point &centre, double distance) const; // voisinage
    QVector<Point> requete(const Voxel &conteneur) const; // dans un voxel

protected:


    Point                   m_centre;
    double                 m_rayon;
private:
};

#endif // OCTREE_H

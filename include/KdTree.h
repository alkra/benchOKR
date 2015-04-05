#ifndef KDTREE_H
#define KDTREE_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe KdTree.
 * Cette classe hérite de Arbre et représente le stockage par la méthode du
 * Kd-tree. */

#include "Arbre.h"


class KdTree : public Arbre  // Création d'une classe KdTree qui hérite de la classe Arbre
{
    public:
        KdTree();
        ~KdTree();

        void construire();
        Point* requete(const Point &centre, double distance) const; // voisinage
        Point* requete(const Voxel &conteneur) const; // dans un voxel
    protected:
    private:
};

#endif // KDTREE_H

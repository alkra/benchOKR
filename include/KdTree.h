#ifndef KDTREE_H
#define KDTREE_H

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

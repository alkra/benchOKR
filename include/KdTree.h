#ifndef KDTREE_H
#define KDTREE_H

#include "Arbre.h"


class KdTree : public Arbre  // Cr�ation d'une classe KdTree qui h�rite de la classe Arbre
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

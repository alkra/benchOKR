#ifndef OCTREE_H
#define OCTREE_H

#include <include/Arbre.h>



class Octree : public Arbre  // Création d'une classe Octree qui hérite de la classe Arbre
{
    public:
        Octree();
        virtual ~Octree();

        void construire();
        Point* requete(const Point &centre, double distance) const; // voisinage
        Point* requete(const Voxel &conteneur) const; // dans un voxel
    protected:
    private:
};

#endif // OCTREE_H

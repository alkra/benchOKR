#ifndef OCTREE_H
#define OCTREE_H

#include <include/Arbre.h>



class Octree : public Arbre  // Cr�ation d'une classe Octree qui h�rite de la classe Arbre
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

#ifndef OCTREE_H
#define OCTREE_H

/* �ENSG 2015
 * �cole nationale des sciences g�ographiques
 * 6-8 avenue Blaise Pascal
 * Cit� Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALL�E CEDEX 2
 * FRANCE */

/* Ce fichier d�finit la classe Octree */

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

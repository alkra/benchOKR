#ifndef OCTREE_H
#define OCTREE_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe Octree */

#include "../include/Arbre.h"
#include "NoeudOctree.h"


class Octree : public Arbre<NoeudOctree>  // Création d'une classe Octree qui hérite de la classe Arbre
{
    public:
        Octree();
        virtual ~Octree();

        void construire();
        QVector<Point> requete(const Point &centre, double distance) const; // voisinage
        QVector<Point> requete(const Voxel &conteneur) const; // dans un voxel
    protected:
    private:
};

#endif // OCTREE_H

#ifndef RTREE_H
#define RTREE_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe RTree. */

#include "include/Arbre.h"
#include "include/NoeudR.h"
#include "include/Point.h"

class RTree : public Arbre
// Création d'une classe RTree qui hérite de la classe Arbre
{
    public:
        RTree();
        ~RTree();

        void construire();
        Point* requete(const Point &centre, double distance) const; // voisinage
        Point* requete(const Voxel &conteneur) const; // dans un voxel
    protected:
    private:
};

#endif // RTREE_H

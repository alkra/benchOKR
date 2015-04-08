/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe RTree. */

#include "../include/RTree.h"

RTree::RTree()
{
    //ctor
}

RTree::~RTree()
{
    //dtor
}

void RTree::construire() {
    // Code spécifique au kd-tree
}

Point* RTree::requete(const Point &centre, double distance) const {
    return racine->requete(centre, distance);
}

Point* RTree::requete(const Voxel &conteneur) const {
    // requête dans un voxel
}

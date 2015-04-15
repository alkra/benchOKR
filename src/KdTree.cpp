/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation de la classe KdTree. */

#include "../include/KdTree.h"

KdTree::KdTree()
{
    //ctor
}

KdTree::~KdTree()
{
    //dtor
}

void KdTree::construire() {
    // Code spécifique au kd-tree
}

QVector<Point> KdTree::requete(const Point &centre, double distance) const {
    // requête sur un voisinage
}

QVector<Point> KdTree::requete(const Voxel &conteneur) const {
    // requête dans un voxel
}

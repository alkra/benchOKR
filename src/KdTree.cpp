#include "include/KdTree.h"

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

Point* KdTree::requete(const Point &centre, double distance) const {
    // requête sur un voisinage
}

Point* KdTree::requete(const Voxel &conteneur) const {
    // requête dans un voxel
}

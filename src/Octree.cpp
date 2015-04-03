#include "include/Octree.h"

Octree::Octree()
{
    //ctor
}

Octree::~Octree()
{
    //dtor
}

void Octree::construire() {
    // Code spécifique à l'octree
}

Point* Octree::requete(const Point &centre, double distance) const {
    // requête sur un voisinage
}

Point* Octree::requete(const Voxel &conteneur) const {
    // requête dans un voxel
}

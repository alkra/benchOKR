/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe Octree. */

#include "../include/Octree.h"

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

QVector<Point> Octree::requete(const Point &centre, double distance) const {
    // requête sur un voisinage
}

QVector<Point> Octree::requete(const Voxel &conteneur) const {
    // requête dans un voxel
}

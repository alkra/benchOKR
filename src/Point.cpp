/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe Point. */

#include "../include/Point.h"

/* Constructeurs */

Point::Point() : Point3D()
{
    //ctor
}

Point::Point(double x, double y, double z) : Point3D(x, y, z) {}

Point::~Point()
{
    //dtor
}

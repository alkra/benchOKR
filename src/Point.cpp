/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe Point. */

#include "include/Point.h"

/* Constructeurs */

Point::Point() : m_x(0), m_y(0), m_z(0)
{
    //ctor
}

Point::Point(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}

Point::~Point()
{
    //dtor
}

/* Accesseurs et mutateurs */

double Point::getX() const {
    return m_x;
}
double Point::getY() const {
    return m_y;
}
double Point::getZ() const {
    return m_z;
}
void Point::setX(double x) {
    m_x = x;
}
void Point::setY(double y) {
    m_y = y;
}
void Point::setZ(double z) {
    m_z = z;
}

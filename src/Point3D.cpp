/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe Point3D */

#include "../include/Point3D.h"

Point3D::Point3D()
{
    //ctor
}

Point3D::Point3D(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}

Point3D::Point3D(const Point3D &autre) : m_x(autre.getX()), m_y(autre.getY()),
m_z(autre.getZ()) {
}

Point3D::~Point3D()
{
    //dtor
}

/* Accesseurs et mutateurs */

double Point3D::getX() const {
    return m_x;
}
double Point3D::getY() const {
    return m_y;
}
double Point3D::getZ() const {
    return m_z;
}
void Point3D::setX(double x) {
    m_x = x;
}
void Point3D::setY(double y) {
    m_y = y;
}
void Point3D::setZ(double z) {
    m_z = z;
}

QString Point3D::toQString() const {
    QString res;
    res.append(QString("%1   %2    %3").arg(m_x).arg(m_y).arg(m_z));
    return res;
}

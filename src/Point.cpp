#include "include/Point.h"

Point::Point() : m_x(0), m_y(0), m_z(0)
{
    //ctor
}

Point(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}

Point::~Point()
{
    //dtor
}

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

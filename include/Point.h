#ifndef POINT_H
#define POINT_H
#include <string>
/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe Point représentant un point du nuage. */

#include "Point3D.h"


class Point: public Point3D
{
public:
    Point& operator+=(const Point &valeur);
    Point& operator-=(const Point &valeur);
    Point& operator*=(const double &valeur);
    Point();
    Point(double x, double y, double z);
    Point(double x, double y, double z,int code);
    Point(const Point3D &autre);

    ~Point();

    unsigned int m_code;  // utilisé au cours de la génération de l'octree

private:



};
Point operator+(Point const &a, Point const &b);
Point operator-(Point const &a, Point const &b);
Point operator*(Point const &a, double const &b);


#endif // POINT_H

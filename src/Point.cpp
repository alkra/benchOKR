/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe Point. */


#include <QCoreApplication>
#include<iostream>
#include<fstream>
#include <string>
#include "../include/Point.h"
using namespace std;

/* Constructeurs */
Point::Point() : m_x(0), m_y(0), m_z(0),m_code(0)
{
    //ctor
}

Point::Point(double x, double y, double z) :Point3D(x,y,z) {}


Point::~Point()
{
    //dtor
}




// les opérateurs de surcharge
// pour effectuer les opérations aritmétiques sur les objets

Point operator+(Point const &a, Point const &b)
{
    Point copie(a);
    copie+=b;
    return copie;
}
Point& Point::operator+=(const Point &val)
{
    m_x = m_x+ val.getX();
    m_y = m_y + val.getY();
    m_z = m_z + val.getZ();

    return *this;
}
Point operator-(Point const &a, Point const &b)
{
    Point copie(a);
    copie-=b;
    return copie;
}
Point& Point::operator-=(const Point &val)
{
    m_x = m_x- val.getX();
    m_y = m_y - val.getY();
    m_z = m_z - val.getZ();


    return *this;
}

Point operator*(Point const &a, double const &b)
{
    Point copie(a);
    copie*=b;
    return copie;
}
Point& Point::operator*=(const double &val)
{
    m_x = m_x* val;
    m_y = m_y * val;
    m_z = m_z * val;


    return *this;
}


Point readPlyBinaire(std::string Path,int line)
{}
Point readTxt(std::string Path,int line)
{}

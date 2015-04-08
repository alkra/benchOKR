#ifndef POINT_H
#define POINT_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe Point représentant un point du nuage. */

#include "Point3D.h"

class Point : public Point3D
{
    public:
        Point();
        Point(double x, double y, double z);
        ~Point();
    protected:
    private:
};

#endif // POINT_H

#ifndef POINT_H
#define POINT_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe Point représentant un point du nuage. */

class Point
{
    public:
        Point();
        Point(double x, double y, double z);
        ~Point();

        double getX() const;
        double getY() const;
        double getZ() const;
        void setX(double x);
        void setY(double y);
        void setZ(double z);
    protected:
    private:

    // attribut de classe point3D
       double m_x;
       double m_y;
       double m_z;
};

#endif // POINT_H

#ifndef POINT3D_H
#define POINT3D_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe Point3D, qui représente le deux coins d'un
 * Voxel. */

class Point3D
{
    public:
        Point3D();
        Point3D(double x, double y, double z);
        ~Point3D();

        double getX() const;
        double getY() const;
        double getZ() const;
        void setX(double x);
        void setY(double y);
        void setZ(double z);

    protected:

    // attributs membres de point3D
    double m_x,m_y,m_z ;


};

#endif // POINT3D_H

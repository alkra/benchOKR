#ifndef VOXEL_H
#define VOXEL_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

#include "include/Point3D.h"
#include "include/Point.h"

/* Définit la classe représentant un voxel parallèle aux axes du repère */
class Voxel {
public:
    Voxel(); // constructeur par défaut
    Voxel(const Point3D &min, const Point3D &max);
    Voxel(double xdeb, double ydeb, double zdeb, double xfin, double yfin, double zfin);
    Voxel(const Voxel &modele); // constructeur de recopie

    /* Méthode */
    bool intersecte(const Point &candidat, bool strict = false) const; // revoie true si le point est dans le voxel

    /* Accesseurs et mutateurs */
    Point3D getDebut() const;
    Point3D getFin() const;
    void setDebut(const Point3D &point);
    void setDebut(double x, double y, double z);
    void setFin(const Point3D &point);
    void setFin(double x, double y, double z);

private:
    Point3D m_debut;
    Point3D m_fin;
};

#endif // VOXEL_H

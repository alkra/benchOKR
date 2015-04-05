/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe Voxel */

#include "include/Voxel.h"

Voxel::Voxel() : m_debut(), m_fin() {} // constructeur par défaut
Voxel::Voxel(const Point3D &min, const Point3D &max) :
    m_debut(min), m_fin(max) {}
Voxel::Voxel(double xdeb, double ydeb, double zdeb,
             double xfin, double yfin, double zfin): m_debut(xdeb, ydeb,zdeb),
                                                     m_fin(xfin, yfin, zfin) {
}

Voxel::Voxel(const Voxel &modele) { // constructeur de recopie
    m_debut = modele.getDebut();
    m_fin = modele.getFin();
}

/* Méthode */
bool Voxel::intersecte(const Point &candidat, bool strict) const {
    /* revoie true si le point est dans le voxel */
    // ...
}

/* Accesseurs et mutateurs */
Point3D Voxel::getDebut() const {
    return m_debut;
}
Point3D Voxel::getFin() const {
    return m_fin;
}
void Voxel::setDebut(const Point3D &point) {
    m_debut = point;
}

void Voxel::setDebut(double x, double y, double z) {
    m_debut.setX(x);
    m_debut.setY(y);
    m_debut.setZ(z);
}

void Voxel::setFin(const Point3D &point) {
    m_fin = point;
}

void Voxel::setFin(double x, double y, double z) {
    m_fin.setX(x);
    m_fin.setY(y);
    m_fin.setZ(z);
}

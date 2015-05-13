/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe Voxel */

#include "../include/Voxel.h"

Voxel::Voxel() : m_debut(), m_fin() {} // constructeur par défaut
Voxel::Voxel(const Point3D &min, const Point3D &max) :
    m_debut(min), m_fin(max) {

}
Voxel::Voxel(double xdeb, double ydeb, double zdeb,
             double xfin, double yfin, double zfin): m_debut(xdeb, ydeb,zdeb),
                                                     m_fin(xfin, yfin, zfin) {
}

Voxel::Voxel(const Voxel &modele) { // constructeur de recopie
    m_debut = modele.getDebut();
    m_fin = modele.getFin();
}

bool operateur_strict(double a, double b) {
    return a < b;
}
bool operateur_large(double a, double b) {
    return a <= b;
}
bool test_dimension(bool inferieur(double, double), double debut, double fin, double candidat) {
    return (
            inferieur(debut, candidat)
         && inferieur(candidat, fin)
            ) || (
            inferieur(fin, candidat)
         && inferieur(candidat, debut)
            );
}

/* Méthode */
bool Voxel::intersecte(const Point3D &candidat, bool strict) const {
    /* Choix de la méthode de comparaison, stricte ou large */
    bool (*inferieur)(double, double);
    if(strict) {
        inferieur = &operateur_strict;
    } else {
        inferieur = &operateur_large;
    }

    return (
        test_dimension(inferieur, m_debut.getX(), m_fin.getX(), candidat.getX())
     && test_dimension(inferieur, m_debut.getY(), m_fin.getY(), candidat.getY())
     && test_dimension(inferieur, m_debut.getZ(), m_fin.getZ(), candidat.getZ())
    );
}

Point3D *Voxel::calcSommets() const {
    Point3D *sommets = new Point3D[8];
    sommets[0] = Point3D(m_debut);
    sommets[1] = Point3D(m_debut.getX(), m_debut.getY(), m_fin.getZ());
    sommets[2] = Point3D(m_debut.getX(), m_fin.getY(), m_debut.getZ());
    sommets[3] = Point3D(m_debut.getX(), m_fin.getY(), m_fin.getZ());
    sommets[4] = Point3D(m_fin.getX(), m_debut.getY(), m_debut.getZ());
    sommets[5] = Point3D(m_fin.getX(), m_debut.getY(), m_fin.getZ());
    sommets[6] = Point3D(m_fin.getX(), m_fin.getY(), m_debut.getZ());
    sommets[7] = Point3D(m_fin);
    return sommets;
}

bool Voxel::intersecte(const Voxel &un, const Voxel &deux, bool strict, bool testerAutreSens) {
    bool res = false;

    Point3D *sommets = deux.calcSommets();
    for(short i = 0; i<8; i++) {
        res = res || un.intersecte(sommets[i], strict);
    }
    delete[] sommets;

    if(res && testerAutreSens) {
        res = res || Voxel::intersecte(deux, un, strict, false);
    }

    return res;
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


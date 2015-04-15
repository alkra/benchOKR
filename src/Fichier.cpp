/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient les méthodes de la classe Fichier. */

#include "../include/Fichier.h"

Fichier::Fichier() : m_fichier(), m_voxel() {

}

Fichier::Fichier(const Fichier &modele) : m_fichier(),
    m_voxel(modele.getVoxel()) {
    m_fichier.setFileName(modele.getFichier().fileName());
}


Fichier& Fichier::operator=(Fichier modele) {
    *this = modele;
    return *this;
}

Fichier::~Fichier()
{
}

bool Fichier::ouvrir(const QString &chemin, QIODevice::OpenMode mode) {
    m_fichier.setFileName(chemin);
    return m_fichier.open(mode);
}

void Fichier::fermer() {
    m_fichier.close();
}


bool Fichier::ajoutPoint(const Point &p, long pos) {
    // à implémenter
}

Point Fichier::getPoint(long pos)
{
    // renvoie le pos-ième point du fichier
}

Point* Fichier::requete(const Point &centre, double distance) const {
    // renvoie tous les points du fichier se trouvant à une distance 'distance' de 'centre'
}

Point* Fichier::requete(const Voxel &conteneur) const {
    // renvoie tous les points du fichier contenus dans 'conteneur'
}

/* Accesseurs et mutateurs (1 par attribut) */
const QFile &Fichier::getFichier() const {
    return m_fichier;
}

void Fichier::setFichier(QFile &nouveau) {

}

Voxel Fichier::getVoxel() const {
    return m_voxel;
}

void Fichier::calculerVoxel() {
    // MARYAME
}

void Fichier::setVoxel(const Voxel &v) {
    // Attention, ne garantit pas que la nouvelle boîte soit cohérente
    // Appeler calculerVoxel plutôt
    m_voxel = v;
}

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient les méthodes de la classe Fichier. */

#include "../include/Fichier.h"

Fichier::Fichier() {
    // euh
}

Fichier::Fichier(const QString chemin)
{
    // ouvrir le fichier "chemin"
}

Fichier::~Fichier()
{
    // fermer le fichier
}

Point Fichier::getPoint(long pos)
{
    // renvoie le pos-ième point du fichier
}

Point* requete(const Point &centre, double distance) {
    // renvoie tous les points du fichier se trouvant à une distance 'distance' de 'centre'
}

Point* requete(const Voxel &conteneur) {
    // renvoie tous les points du fichier contenus dans 'conteneur'
}

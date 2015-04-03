#include "../include/Fichier.h"

Fichier::Fichier(QString chemin)
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

Point* requete(const Point &centre, double distance) const {
    // renvoie tous les points du fichier se trouvant à une distance 'distance' de 'centre'
}

Point* requete(const Voxel &conteneur) const {
    // renvoie tous les points du fichier contenus dans 'conteneur'
}

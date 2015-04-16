/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe NoeudOctree
 */

#include "../include/NoeudOctree.h"


NoeudOctree::NoeudOctree() : Noeud() {
}

/* Les fonctions de requête */
QVector<Point> NoeudOctree::requete(const Point &centre, double distance) const {
    // renvoie tous les points de tous les enfants se trouvant dans le voisinage
}

QVector<Point> NoeudOctree::requete(const Voxel &conteneur) const {
}

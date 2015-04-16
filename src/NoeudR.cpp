/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe NoeudR. */

#include "../include/NoeudR.h"


NoeudR::NoeudR() : Noeud() {
}

NoeudR::NoeudR(const NoeudR & modele) : Noeud(modele) {
}


/* Les fonctions de requête */
QVector<Point> NoeudR::requete(const Point &centre, double distance) const {

}

QVector<Point> NoeudR::requete(const Voxel &conteneur) const {
    // renvoie tous les points de tous les enfants contenus dans le conteneur
    // Algorithme de Gutmann

    QVector<Point> resultat, res_requete;

    if(m_terminal) { // Gut84 - S2
        res_requete = m_fichier->requete(conteneur);
    }

    else { // Gut84 - S1
        for(long i = 0 ; i < m_nb_enfants ; i++) {
            if(Voxel::intersecte(m_enfants[i].getVoxel(), conteneur)) {
                res_requete = m_enfants[i].requete(conteneur);
                resultat += res_requete;
            }
        }
    }

    return resultat;
}

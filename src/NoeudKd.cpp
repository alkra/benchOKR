/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe NoeudKd. */

#include "../include/NoeudKd.h"
#include"string"

using namespace std;



NoeudKd::NoeudKd(bool terminal) : Noeud(terminal) {
}
NoeudKd::NoeudKd(QString cheminRelatif, bool terminal)
    : Noeud(cheminRelatif, terminal) { // construit un nœud
}
NoeudKd::NoeudKd(Voxel &boite, QString cheminRelatif, bool terminal)
    : Noeud(boite, cheminRelatif, terminal) {
}
NoeudKd::NoeudKd(const NoeudKd &modele) : Noeud(modele) {
}
NoeudKd::~NoeudKd() {
}

/* Les fonctions de requête */
QVector<Point> NoeudKd::requete(const Point &centre, double distance) const {
    // renvoie tous les points de tous les enfants se trouvant dans le voisinage
}

QVector<Point> NoeudKd::requete(const Voxel &conteneur) const {
    QVector<Point> resultat;
    if(m_terminal) {
        return m_fichier->getVPoints(); // les points contenus dans ce noeud
    }

    for (int i = 0; i < m_nb_enfants ; i++) {
        if(Voxel::intersecte(m_enfants[i].getVoxel(), conteneur)) {
            resultat += m_enfants[i].requete(conteneur);
        }
    }

    return resultat;
}

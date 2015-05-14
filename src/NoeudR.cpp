/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe NoeudR. */

#include "../include/NoeudR.h"


NoeudR::NoeudR(bool terminal) : Noeud(terminal), m_parent(NULL) {
}

NoeudR::NoeudR(NoeudR *parent, bool terminal) :
    Noeud(terminal), m_parent(parent) {
}

NoeudR::NoeudR(const NoeudR & modele) : Noeud(modele) {
}

NoeudR::~NoeudR() {
}


NoeudR* NoeudR::getParent() const {
    return m_parent;
}
void NoeudR::setParent(NoeudR *parent) {
    m_parent = parent;
}

void NoeudR::setEnfant(NoeudR &nouveau, long pos)
    throw(TerminalErreur, IndiceHorsDomaine) {
    Noeud::setEnfant(nouveau, pos);
    nouveau.setParent(this);
}

void NoeudR::ajoutEnfant(NoeudR &nouveau, long pos)
    throw(TerminalErreur, IndiceHorsDomaine) {
    Noeud::ajoutEnfant(nouveau, pos);
    nouveau.setParent(this);
}


/* Les fonctions de requête */
QVector<Point> NoeudR::requete(const Point &centre, double distance) const {
    Voxel v(centre.getX() - distance,
            centre.getY() - distance,
            centre.getZ() - distance,
            centre.getX() + distance,
            centre.getY() + distance,
            centre.getZ() + distance);
    return NoeudR::requete(v);
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

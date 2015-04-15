/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe NoeudOctree
 */

#include "../include/NoeudOctree.h"


NoeudOctree::NoeudOctree() : Noeud() {/*
    // construit un noeud normal
    m_enfants.fils = new NoeudOctree[];
    m_taille_enfants = ;*/
}
NoeudOctree::NoeudOctree(bool terminal) : Noeud(terminal) { /*
    // construit un noeud terminal (ou non)
    if(terminal) {
        m_enfants.feuille = new Fichier[];
        m_taille_enfants = ;
    } else {
        m_enfants.fils = new NoeudOctree[];
        m_taille_enfants = ;
    }*/
}

NoeudOctree::NoeudOctree(Voxel &boite, bool terminal): Noeud(boite, terminal)
{ /*
    if(terminal) {
        m_enfants.feuille = new Fichier[];
        m_taille_enfants = ;
    } else {
        m_enfants.fils = new NoeudOctree[];
        m_taille_enfants = ;
    }*/
}

NoeudOctree::NoeudOctree(const NoeudOctree &modele) : Noeud(modele) { /*
    m_terminal = modele.est_terminal();
    m_boite = modele.getVoxel();
    m_taille_enfants = modele.getTailleEnfants();
    if(m_terminal) {
        m_enfants.feuille = new Fichier[m_taille_enfants]();
    } else {
        m_enfants.fils = new NoeudOctree[m_taille_enfants]();
    }
    long i = 0;
    const union Noeud::NoeudSelonProfondeur enfantsModele = modele.getEnfants();

    for(i=0 ; i<m_taille_enfants ; i++) { // recopie du tableau
        if(m_terminal) {
            m_enfants.feuille[i] = enfantsModele.feuille[i];
        } else {
            m_enfants.fils[i] = enfantsModele.fils[i];
        }
    }*/
}

/* Les fonctions de requête */
QVector<Point> NoeudOctree::requete(const Point &centre, double distance) const {
    // renvoie tous les points de tous les enfants se trouvant dans le voisinage
}

QVector<Point> NoeudOctree::requete(const Voxel &conteneur) const {

}

/* Accesseur */
void NoeudOctree::setEnfant(long pos, NoeudOctree &noeud) throw(ErreurAffectationTerminal) {
    // remplace le pos-ième enfant par "noeud"
    if(m_terminal) {
        throw new ErreurAffectationTerminal;
    } else {
        m_enfants.fils[pos] = noeud;
    }
}

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe NoeudKd. */

#include "include/NoeudKd.h"

/*
NoeudKd::NoeudKd() : m_terminal(false), m_boite() { // construit un noeud normal
    m_enfants.fils = new NoeudKd[];
    m_taille_enfants = ;
}
NoeudKd::NoeudKd(bool terminal = false) : m_terminal(terminal), m_boite() { // construit un noeud terminal (ou non)
    if(terminal) {
        m_enfants.feuille = new Fichier[];
        m_taille_enfants = ;
    } else {
        m_enfants.fils = new NoeudKd[];
        m_taille_enfants = ;
    }
}

NoeudKd::NoeudKd(Voxel &boite, bool terminal = false) : m_boite(boite), m_terminal(terminal) {
    if(terminal) {
        m_enfants.feuille = new Fichier[];
        m_taille_enfants = ;
    } else {
        m_enfants.fils = new NoeudKd[];
        m_taille_enfants = ;
    }
}*/


NoeudKd::NoeudKd(const NoeudKd &modele) { // Constructeur de recopie
    m_terminal = modele.est_terminal();
    m_boite = modele.getVoxel();
    m_taille_enfants = modele.getTailleEnfants();
    if(terminal) {
        m_enfants.feuille = new Fichier[m_taille_enfants];
    } else {
        m_enfants.fils = new NoeudKd[m_taille_enfants];
    }
    long i = 0;
    union NoeudSelonProfondeur *enfantsModele = modele.getEnfants();

    for(i=0 ; i<m_taille_enfants ; i++) { // recopie du tableau
        if(terminal) {
            m_enfants.feuille[i] = enfantsModele->feuille[i];
        } else {
            m_enfants.fils[i] = enfantsModele->fils[i];
        }
    }
}

/* Les fonctions de requête */
Point* NoeudKd::requete(const Point &centre, double distance) const {
    // renvoie tous les points de tous les enfants se trouvant dans le voisinage
}

Point* NoeudKd::requete(const Voxel &conteneur) const {
    // renvoie tous les points de tous les enfants contenus dans le conteneur
}

/* Accesseur */
void NoeudKd::setEnfant(long pos, NoeudKd &noeud) {  // remplace le pos-ième enfant par "noeud"
    if(m_terminal) {
        throw termAffectErreur;
    } else {
        m_enfants[pos].fils = noeud;
    }
}

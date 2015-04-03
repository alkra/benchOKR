#include "include/NoeudOctree.h"

/*
NoeudOctree::NoeudOctree() : m_terminal(false), m_boite() { // construit un noeud normal
    m_enfants.fils = new NoeudOctree[];
    m_taille_enfants = ;
}
NoeudOctree::NoeudOctree(bool terminal = false) : m_terminal(terminal), m_boite() { // construit un noeud terminal (ou non)
    if(terminal) {
        m_enfants.feuille = new Fichier[];
        m_taille_enfants = ;
    } else {
        m_enfants.fils = new NoeudOctree[];
        m_taille_enfants = ;
    }
}

NoeudOctree::NoeudOctree(Voxel &boite, bool terminal = false) : m_boite(boite), m_terminal(terminal) {
    if(terminal) {
        m_enfants.feuille = new Fichier[];
        m_taille_enfants = ;
    } else {
        m_enfants.fils = new NoeudOctree[];
        m_taille_enfants = ;
    }
}*/

NoeudOctree::NoeudOctree(const NoeudOctree &modele) { // Constructeur de recopie
    m_terminal = modele.est_terminal();
    m_boite = modele.getVoxel();
    m_taille_enfants = modele.getTailleEnfants();
    if(terminal) {
        m_enfants.feuille = new Fichier[m_taille_enfants];
    } else {
        m_enfants.fils = new NoeudOctree[m_taille_enfants];
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
Point* NoeudOctree::requete(const Point &centre, double distance) const {
    // renvoie tous les points de tous les enfants se trouvant dans le voisinage
}

Point* NoeudOctree::requete(const Voxel &conteneur) const {
    // renvoie tous les points de tous les enfants contenus dans le conteneur
}

/* Accesseur */
void NoeudOctree::setEnfant(long pos, NoeudOctree &noeud) {  // remplace le pos-ième enfant par "noeud"
    if(m_terminal) {
        throw termAffectErreur;
    } else {
        m_enfants[pos].fils = noeud;
    }
}

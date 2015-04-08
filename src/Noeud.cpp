/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe Noeud. */

#include "../include/Noeud.h"

/* Méthodes virtuelles */
Noeud::Noeud() : m_terminal(false), m_boite() { // construit un noeud normal
    /* m_enfants.fils = new Noeud[1];
    m_taille_enfants = 1; */
}

Noeud::Noeud(bool terminal) : m_terminal(terminal), m_boite() {/*
    // construit un noeud terminal (ou non)
    if(terminal) {
        m_enfants.feuille = new Fichier[1];
        m_taille_enfants = 1;
    } else {
        m_enfants.fils = new Noeud[1];
        m_taille_enfants = 1;
    }*/
}

Noeud::Noeud(Voxel &boite, bool terminal) :
       m_terminal(terminal), m_boite(boite) {/*
    if(terminal) {
        m_enfants.feuille = new Fichier[1];
        m_taille_enfants = 1;
    } else {
        m_enfants.fils = new Noeud[1];
        m_taille_enfants = 1;
    }*/
}

Noeud::Noeud(const Noeud &modele) { /* // Constructeur de recopie
    m_terminal = modele.est_terminal();
    m_boite = modele.getVoxel();
    m_taille_enfants = modele.getTailleEnfants();
    if(m_terminal) {
        m_enfants.feuille = new Fichier[m_taille_enfants];
    } else {
        m_enfants.fils = new Noeud[m_taille_enfants]();
    }
    long i = 0;
    union NoeudSelonProfondeur *enfantsModele = modele.getEnfants();

    for(i=0 ; i<m_taille_enfants ; i++) { // recopie du tableau
        if(terminal) {
            m_enfants.feuille[i] = enfantsModele->feuille[i];
        } else {
            m_enfants.fils[i] = enfantsModele->fils[i];
        }
    }*/
}

Noeud::~Noeud() {
}


long Noeud::getTailleEnfants() const {
    // renvoie la longueur du tableau d'enfants
    return m_taille_enfants;
}

Noeud& Noeud::getFils(long pos) const throw(ErreurAccesIntermediaire) {
    // retourne le pos-ième enfant si c'est un noeud
    if(m_terminal) {
        throw new ErreurAccesIntermediaire;
    } else {
        return m_enfants.fils[pos];
    }
}

Fichier& Noeud::getFeuille(long pos) const throw(ErreurAccesTerminal) {
    // retourne le pos-ième enfant si c'est une feuille
    if(m_terminal) {
        return m_enfants.feuille[pos];
    } else {
        throw new ErreurAccesTerminal;
    }
}

void Noeud::setEnfant(long pos, Noeud &noeud) throw(ErreurAffectationTerminal) {
    // remplace le pos-ième enfant par "noeud"
    if(m_terminal) {
        throw new ErreurAffectationTerminal;
    } else {
        m_enfants.fils[pos] = noeud;
    }
}

void Noeud::setEnfant(long pos, Fichier &feuille) throw(ErreurAffectationIntermediaire) {
    // remplace le pos-ième enfant par "feuille"
    if(m_terminal) {
        m_enfants.feuille[pos] = feuille;
    } else {
        throw new ErreurAffectationIntermediaire;
    }
}

const Noeud::NoeudSelonProfondeur Noeud::getEnfants() const {
    // retourne le tableau d'enfants (pourquoi faire ?)
    return m_enfants;
}

void Noeud::setEnfants(union NoeudSelonProfondeur enfants, long taille,
                       bool terminal) {
    // remplace le tableau d'enfants (DANGEREUX !)
    m_enfants = enfants;
    m_terminal = terminal;
    m_taille_enfants = taille;
}

Voxel Noeud::getVoxel() const {
    return m_boite;
}

void Noeud::setVoxel(Voxel &v) {
    m_boite = v;
}

bool Noeud::est_terminal() const {
    return m_terminal;
}

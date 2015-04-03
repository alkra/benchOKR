#include "include/Noeud.h"

/* Méthodes virtuelles *
Noeud::Noeud() : m_terminal(false), m_boite() { // construit un noeud normal
    m_enfants.fils = new Noeud[1];
    m_taille_enfants = 1;
}
Noeud::Noeud(bool terminal = false) : m_terminal(terminal), m_boite() { // construit un noeud terminal (ou non)
    if(terminal) {
        m_enfants.feuille = new Fichier[1];
        m_taille_enfants = 1;
    } else {
        m_enfants.fils = new Noeud[1];
        m_taille_enfants = 1;
    }
}

Noeud::Noeud(Voxel &boite, bool terminal = false) : m_boite(boite), m_terminal(terminal) {
    if(terminal) {
        m_enfants.feuille = new Fichier[1];
        m_taille_enfants = 1;
    } else {
        m_enfants.fils = new Noeud[1];
        m_taille_enfants = 1;
    }
}

Noeud::Noeud(const Noeud &modele) { // Constructeur de recopie
    m_terminal = modele.est_terminal();
    m_boite = modele.getVoxel();
    m_taille_enfants = modele.getTailleEnfants();
    if(terminal) {
        m_enfants.feuille = new Fichier[m_taille_enfants];
    } else {
        m_enfants.fils = new Noeud[m_taille_enfants];
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

// */

Noeud::~Noeud() { // destructeur
    delete[] m_enfants;
}

long Noeud::getTailleEnfants() const { // renvoie la longueur du tableau d'enfants
    return m_taille_enfants;
}

Noeud& Noeud::getFils(long pos) const { // retourne le pos-ième enfant si c'est un noeud
    if(m_terminal) {
        throw intermedAccesErreur;
    } else {
        return m_enfants[pos].fils;
    }
}

Fichier& Noeud::getFeuille(long pos) const { // retourne le pos-ième enfant si c'est une feuille
    if(m_terminal) {
        return m_enfants[pos].feuille;
    } else {
        throw termAccesErreur;
    }
}

void Noeud::setEnfant(long pos, Noeud &noeud) { // remplace le pos-ième enfant par "noeud"
    if(m_terminal) {
        throw termAffectErreur;
    } else {
        m_enfants[pos].fils = noeud;
    }
}

void Noeud::setEnfant(long pos, Fichier &feuille) { // remplace le pos-ième enfant par "feuille"
    if(m_terminal) {
        m_enfants[pos].feuille = feuille;
    } else {
        throw intermedAffectErreur;
    }
}

const Noeud::NoeudSelonProfondeur *Noeud::getEnfants() const { // retourne le tableau d'enfants (pourquoi faire ?)
    return m_enfants;
}

void Noeud::setEnfants(union NoeudSelonProfondeur enfants[], long taille, bool terminal) { // remplace le tableau d'enfants (DANGEREUX !)
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

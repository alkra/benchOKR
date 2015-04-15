/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe NoeudR. */

#include "../include/NoeudR.h"


NoeudR::NoeudR() : Noeud() { // construit un noeud normal
    /*m_enfants.fils = new NoeudR[];
    m_taille_enfants = ;*/
}

NoeudR::NoeudR(bool terminal) : Noeud(terminal) { /* // construit un noeud terminal (ou non)
    if(terminal) {
        m_enfants.feuille = new Fichier[];
        m_taille_enfants = ;
    } else {
        m_enfants.fils = new NoeudR[];
        m_taille_enfants = ;
    }*/
}

NoeudR::NoeudR(Voxel &boite, bool terminal) : Noeud(boite, terminal) {/*
    if(terminal) {
        m_enfants.feuille = new Fichier[];
        m_taille_enfants = ;
    } else {
        m_enfants.fils = new NoeudR[];
        m_taille_enfants = ;
    }*/
}

NoeudR::NoeudR(const NoeudR &modele) : Noeud(modele) { /* // Constructeur de recopie
    m_terminal = modele.est_terminal();
    m_boite = modele.getVoxel();
    m_taille_enfants = modele.getTailleEnfants();
    if(m_terminal) {
        m_enfants.feuille = new Fichier[m_taille_enfants]();
    } else {
        m_enfants.fils = new NoeudR[m_taille_enfants]();
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
QVector<Point> NoeudR::requete(const Point &centre, double distance)
    const {

}

QVector<Point> NoeudR::requete(const Voxel &conteneur) const {
    // renvoie tous les points de tous les enfants contenus dans le conteneur
    // Algorithme de Gutmann

    QVector<Point> resultat, res_requete;

    if(m_terminal) { // Gut84 - S2
        Fichier *feuilles = m_enfants.feuille;
        for(long i = 0 ; i < m_taille_enfants ; i++) {
            if(Voxel::intersecte(feuilles[i].getVoxel(), conteneur)) {
                res_requete = feuilles[i].requete(conteneur);
                resultat += res_requete;
            }
        }
    }
    else { // Gut84 - S1
        Noeud *fils = m_enfants.fils;
        for(long i = 0 ; i < m_taille_enfants ; i++) {
            if(Voxel::intersecte(fils[i].getVoxel(), conteneur)) {
                res_requete = fils[i].requete(conteneur);
                resultat += res_requete;
            }
        }
    }
}

/* Accesseur */
void NoeudR::setEnfant(long pos, NoeudR &noeud) throw(ErreurAffectationTerminal) {
    // remplace le pos-ième enfant par "noeud"
    if(m_terminal) {
        throw new ErreurAffectationTerminal;
    } else {
        m_enfants.fils[pos] = noeud;
    }
}

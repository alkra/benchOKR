/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe Noeud. */

#include "../include/Noeud.h"

/* Constructeurs */
Noeud::Noeud() : m_boite(), m_enfants(NULL), m_nb_enfants(0), m_dossier(),
    m_fichier(), m_terminal(false) { // construit un noeud par défaut
}

Noeud::Noeud(QString cheminRelatif): m_boite(), m_enfants(NULL),
    m_nb_enfants(0), m_dossier(cheminRelatif), m_fichier(), m_terminal(false)
{ // construit un nœud
}

Noeud::Noeud(Voxel &boite, QString cheminRelatif) : m_boite(boite),
    m_enfants(NULL), m_nb_enfants(0), m_dossier(cheminRelatif),
    m_fichier(), m_terminal(false) { // construit un noeud en lui associant un Voxel
}

Noeud::Noeud(const Noeud &modele) : m_fichier() { // constructeur de recopie
    m_boite = modele.getVoxel();
    m_nb_enfants = modele.getNbEnfants();
    m_enfants = new Noeud[m_nb_enfants];
    for(long i = 0 ; i < m_nb_enfants ; i++) {
        m_enfants[i] = modele.getEnfant(i);
    }
    m_dossier = modele.getDossier();
    m_terminal = modele.estTerminal();
    if(m_terminal) {
        m_fichier = modele.getFichier();
    }
}

Noeud::~Noeud() { // destructeur
    m_fichier.fermer();
    delete[] m_enfants;
}


Voxel Noeud::getVoxel() const {
    return m_boite;
}

void Noeud::setVoxel(const Voxel &boite) {
    m_boite = boite;
}

Voxel Noeud::calculerVoxel() {
    if(m_terminal) {
        m_boite = m_fichier.calculerVoxel();
    } else {
        double xmin, xmax, ymin, ymax, zmin, zmax;
        Point3D *un, *deux;
        for(long i=0 ; i < m_nb_enfants ; i++) {
            *un = m_enfants[i].getVoxel().getDebut();
            *deux = m_enfants[i].getVoxel().getFin();
            if(i == 0) {
                xmin = un->getX();
                ymin = un->getY();
                zmin = un->getZ();
                xmin = deux->getX();
                ymin = deux->getY();
                zmin = deux->getZ();
            } else {
                if(un->getX() < deux->getX()) {
                    xmin = min<double>(xmin, un->getX());
                    xmax = max<double>(xmax, deux->getX());
                    arrêt
            }
        }
    }
}

Noeud getEnfant(long pos) const;
void setEnfant(Noeud &nouveau, long pos);
bool ajoutEnfant(Noeud &nouveau, long pos = -1);
Noeud supprimerEnfant(long pos = -1);

long getNbEnfants() const;

QDir getDossier() const;
bool setDossier(const QString &nouveau);
bool setDossier(QDir &nouveau);

Fichier& getFichier() const throw(TerminalErreur);
void setFichier(const Fichier &nouveau);

bool estTerminal() const;

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe Noeud. */

#ifndef NOEUD_CPP
#define NOEUD_CPP

#include "../include/Noeud.h"

/* Constructeurs */
NOEUD()::Noeud() : m_defaut(true), m_boite(), m_enfants(NULL), m_nb_enfants(0),
    m_dossier(), m_fichier(NULL), m_terminal(false) { // construit un noeud par défaut
}

NOEUD()::Noeud(QString cheminRelatif): m_defaut(false), m_boite(),
    m_enfants(NULL), m_nb_enfants(0), m_dossier(cheminRelatif), m_fichier(NULL),
    m_terminal(false) { // construit un nœud
}

NOEUD()::Noeud(Voxel &boite, QString cheminRelatif) : m_defaut(false),
    m_boite(boite), m_enfants(NULL), m_nb_enfants(0),m_dossier(cheminRelatif),
    m_fichier(NULL), m_terminal(false) { // construit un noeud en lui associant un Voxel
}

NOEUD()::Noeud(const Noeud<Nd, MAX_ENFANTS> &modele) : m_fichier(NULL) { // constructeur de recopie
    m_defaut = modele.estDefaut();
    m_boite = modele.getVoxel();
    m_nb_enfants = modele.getNbEnfants();
    m_terminal = modele.estTerminal();
    if(m_terminal) {
        m_fichier = modele.getFichier();
    } else {
        m_enfants = new Nd[MAX_ENFANTS];
        for(long i = 0 ; i < m_nb_enfants ; i++) {
            m_enfants[i] = modele.getEnfant<Nd>(i);
        }
    }
    m_dossier = modele.getDossier();
}

NOEUD()::~Noeud() { // destructeur
    m_fichier->fermer();
    delete m_fichier;
    delete[] m_enfants;
}

/* Accesseurs et mutateurs */

NOEUD(bool)::estDefaut() const {
    return m_defaut;
}

NOEUD(Voxel)::getVoxel() const {
    return m_boite;
}

NOEUD(void)::setVoxel(const Voxel &boite) {
    m_defaut = false;
    m_boite = boite;
}


NOEUD(void)::calculerVoxel() {
    if(m_terminal) {
        m_boite = m_fichier->calculerVoxel();
    } else {
        /* On calcule le : */
        double xmin, xmax, ymin, ymax, zmin, zmax;
        /* de l'ensemble des voxels de tous les enfants. */

        Point3D *un, *deux;
        for(long i=0 ; i < m_nb_enfants ; i++) {
            *un = m_enfants[i].getVoxel().getDebut();
            *deux = m_enfants[i].getVoxel().getFin();
            if(i == 0) { // initialisation
                m_defaut = false;
                xmin = un->getX();
                ymin = un->getY();
                zmin = un->getZ();
                xmin = deux->getX();
                ymin = deux->getY();
                zmin = deux->getZ();
            } else {
                if(un->getX() < deux->getX()) {
                    xmin = std::min<double>(xmin, un->getX());
                    xmax = std::max<double>(xmax, deux->getX());
                } else {
                    xmin = std::min<double>(xmin, deux->getX());
                    xmax = std::max<double>(xmax, un->getX());
                }
                if(un->getY() < deux->getY()) {
                    ymin = std::min<double>(ymin, un->getY());
                    ymax = std::max<double>(ymax, deux->getY());
                } else {
                    ymin = std::min<double>(ymin, deux->getY());
                    ymax = std::max<double>(ymax, un->getY());
                }
                if(un->getZ() < deux->getZ()) {
                    zmin = std::min<double>(zmin, un->getZ());
                    zmax = std::max<double>(zmax, deux->getZ());
                } else {
                    zmin = std::min<double>(zmin, deux->getZ());
                    zmax = std::max<double>(zmax, un->getZ());
                }
            }
        }

        m_boite = Voxel(xmin, ymin, zmin, xmax, ymax, zmax);
    }
}

NOEUD(template <typename retour> retour)::getEnfant(long pos) const throw(TerminalErreur, IndiceHorsDomaine) {
    if(pos < 0 || pos >= MAX_ENFANTS) {
        throw new IndiceHorsDomaine(pos, 0, MAX_ENFANTS);
    } else {
        return m_enfants[pos];
    }
}

NOEUD(void)::setEnfant(Nd &nouveau, long pos) throw(TerminalErreur, IndiceHorsDomaine) {
    if(m_terminal) { // Un noeud terminal n'a pas d'enfants
        throw new TerminalErreur(TERMINAL);
    } // else

    if(pos < 0 || pos >= MAX_ENFANTS) { // Position incorrecte
        throw new IndiceHorsDomaine(pos, 0, MAX_ENFANTS);
    } // else

    if(nouveau.estDefaut()) { // cela revient à une suppression
        supprimerEnfant(pos);
        return;
    }

    // on va maintenant modifier un noeud
    m_defaut = false;

    if(m_enfants == NULL) { // noeud pas terminal mais non initialisé
        m_enfants = new Nd[MAX_ENFANTS];
    }

    m_enfants[pos] = nouveau;
    if(m_nb_enfants < pos) {
        m_nb_enfants = pos;
    }
}

NOEUD(bool)::ajoutEnfant(Nd &nouveau, long pos) throw(TerminalErreur, IndiceHorsDomaine) {
    if(m_terminal) { // Un noeud terminal n'a pas d'enfants
        throw new TerminalErreur(TERMINAL);
    } // else

    if(pos != -1 && (pos < 0 || pos >= MAX_ENFANTS)) { // Position incorrecte
        throw new IndiceHorsDomaine(pos, 0, MAX_ENFANTS);
    } // else

    if(m_nb_enfants == MAX_ENFANTS) { // on ne va pas pouvoir ajouter celui-ci
        return false;
    } // else

    // on va maintenant modifier le noeud
    m_defaut = false;

    if(m_enfants == NULL) { // noeud pas terminal mais non initialisé
        m_enfants = new Nd[MAX_ENFANTS];
    }

    if(pos == -1) { // ajout à la fin
        m_enfants[m_nb_enfants] = nouveau;
    } else {
        // on décale
        Nd tmp;
        for(long i=pos ; i < m_nb_enfants ; i++) {
            tmp = m_enfants[i+1];
            m_enfants[i+1] = m_enfants[i];
        }

        // on ajoute
        m_enfants[pos] = nouveau;
    }

    // ajout effectué
    m_nb_enfants++;
    return true;
}

NOEUD(template <typename retour> retour)::supprimerEnfant(long pos) throw(TerminalErreur,IndiceHorsDomaine) {
    if(m_terminal) { // Un noeud terminal n'a pas d'enfants
        throw new TerminalErreur(TERMINAL);
    } // else

    if(pos != -1 && (pos < 0 || pos >= MAX_ENFANTS)) { // Position incorrecte
        throw new IndiceHorsDomaine(pos, 0, MAX_ENFANTS);
    } // else

    Nd resultat;

    if(m_nb_enfants == 0) { // rien à supprimer
        return resultat;
    } // else

    if(pos == -1) { // on supprime le dernier
        resultat = m_enfants[m_nb_enfants -1];
    } else {
        resultat = m_enfants[pos];

        // on décale
        for(long i = pos; i < m_nb_enfants-1 ; i++) {
            m_enfants[i] = m_enfants[i+1];
        }
    }

    // la suppression s'est bien déroulée
    m_enfants[m_nb_enfants-1] = Nd();
    m_nb_enfants--;
    return resultat;
}

NOEUD(long)::getNbEnfants() const {
    return m_nb_enfants;
}

NOEUD(long)::getNbMaxEnfants() const {
    return MAX_ENFANTS;
}

NOEUD(QDir)::getDossier() const {
    return m_dossier;
}

NOEUD(template <class T> bool)::setDossier(const T &nouveau){
    return m_dossier = QDir(nouveau);
}

NOEUD(Fichier*)::getFichier() const
throw(TerminalErreur) {
    if(!m_terminal) {
        throw new TerminalErreur(PAS_TERMINAL);
    } // else

    return m_fichier;
}

NOEUD(void)::setFichier(const Fichier &nouveau) throw(TerminalErreur) {
    if(m_nb_enfants > 0) { // on n'écrase pas le contenu
        throw TerminalErreur(PAS_TERMINAL);
    } // else

    if(!m_terminal) { // il y a peut-être du contenu à effacer
        if(m_enfants != NULL) { // noeud initialisé mais vide
            delete[] m_enfants;
        }
        m_terminal = true;
    }

    m_fichier->fermer();
    m_fichier = nouveau;
}

NOEUD(bool)::estTerminal() const {
    return m_terminal;
}

#endif // NOEUD_CPP

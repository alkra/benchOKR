#ifndef NOEUD_H
#define NOEUD_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe générique Noeud et les exceptions qui y sont
 * associées.
 * Le Noeud d'un arbre peut être soit un noeud intermédiaire qui contient un
 * tableau de Noeud (penser à redéfinir les accesseurs et mutateurs lors de la
 * généralisation), soit un noeud terminal qui contient un tableau de feuilles
 * (de type Fichier).
 * Cette alternative doit être gérée proprement : comme toutes nos méthodes
 * font intervenir des arbres presque équilibrés, on impose que tous les
 * enfants d'un noeud sont de même type. Nos méthodes définissent toujours un
 * nombre maximum d'enfants. Lorsqu'on tente une opération incorrecte, une des
 * quatre exceptions est levée : à récupérer ! */

#include "../include/Point.h"
#include "../include/Voxel.h"
#include "../include/Fichier.h"

#include <QDir>

#define NOEUD(type) template <class Nd, int MAX_ENFANTS> type Noeud<Nd, MAX_ENFANTS>

class IndiceHorsDomaine : public std::exception {
public:
    IndiceHorsDomaine() : m_demande(0), m_min(-1), m_max(-1) {
        m_texte = "L'indice demandé est incorrect.";
    }

    IndiceHorsDomaine(int demande, int min = -1, int max = -1) :
        m_demande(demande), m_min(min), m_max(max) {
        m_texte += QString("L'indice %1 est incorrect.").arg(m_demande);
        if(m_min >= 0 && m_max >= 0) {
            m_texte += QString(" Doit être compris entre %1 et %2.").arg(
                        m_min).arg(m_max);
        } else if(m_min >= 0) {
            m_texte += QString(" Doit être plus grand que %1.").arg(m_min);
        } else if(m_max >= 0) {
            m_texte += QString(" Ne doit pas dépasser %1.").arg(m_max);
        }
        m_texte += "\n";
    }

    int getDemande() const { return m_demande; }
    int getMin() const { return m_min; }
    int getMax() const { return m_max; }
    QString message() const { return m_texte; }

    const char* what() const throw() {
        QByteArray message = m_texte.toLocal8Bit();
        return message.data();
    }

protected:
    int m_demande, m_min, m_max;
    QString m_texte;
};


template <class Nd, int MAX_ENFANTS>
class Noeud
{
protected:
    bool m_defaut; // vrai si le noeud est le noeud par défaut
    Voxel m_boite;
    Nd *m_enfants; // le tableau des enfants
    long m_nb_enfants; // sa taille
    QDir m_dossier; // le dossier du nœud
    Fichier *m_fichier; // le fichier associé, si le noeud est terminal
    bool m_terminal; // vrai si le noeud est terminal


public:
    class TerminalErreur : public std::exception {
    public:
#define TERMINAL "Ce nœud est terminal et n'a pas d'enfants.\n"
#define PAS_TERMINAL "Ce nœud n'est pas terminal et n'est pas associé à un fichier.\n"
        TerminalErreur(char *message) : m_message(message) {}
        const char* what() const throw() {
            return m_message;
        }
    protected:
        char *m_message;
    };

    Noeud(); // construit un noeud par défaut
    Noeud(QString cheminRelatif); // construit un nœud
    Noeud(Voxel &boite, QString cheminRelatif); // construit un noeud en lui associant un Voxel
    Noeud(const Noeud &modele); // constructeur de recopie
    //Noeud& operator= (const Noeud modele);
    ~Noeud(); // destructeur

    /* Les fonctions de requête */
    virtual QVector<Point> requete(const Point &centre, double distance) const =0; // renvoie tous les points de tous les enfants se trouvant dans le voisinage
    virtual QVector<Point> requete(const Voxel &conteneur) const =0; // renvoie tous les points de tous les enfants contenus dans le conteneur

    /* Accesseurs et mutateurs */
    bool estDefaut() const;

    Voxel getVoxel() const;
    void setVoxel(const Voxel &boite);
    void calculerVoxel();

    template <typename retour> retour getEnfant(long pos) const throw(TerminalErreur, IndiceHorsDomaine);
    void setEnfant(Nd &nouveau, long pos)
        throw(TerminalErreur, IndiceHorsDomaine);
    bool ajoutEnfant(Nd &nouveau, long pos = -1)
        throw(TerminalErreur, IndiceHorsDomaine);
    template <typename retour> retour supprimerEnfant(long pos = -1) throw(TerminalErreur,IndiceHorsDomaine);

    long getNbEnfants() const; // le nombre d'enfants effectif

    long getNbMaxEnfants() const; // le nombre maximal d'enfants possible

    QDir getDossier() const;
    template <class T> bool setDossier(const T &nouveau);

    Fichier* getFichier() const throw(TerminalErreur);
    void setFichier(const Fichier &nouveau) throw(TerminalErreur);

    bool estTerminal() const;
};

#include "../src/Noeud.cpp" // pour le fonctions templatées

#endif // NOEUD_H

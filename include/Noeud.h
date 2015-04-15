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


class TerminalErreur : public std::exception {
    const char* what() const throw() {
        return "Ce nœud n'est pas terminal.";
    }
};


class Noeud
{
    public:
        Noeud(); // construit un noeud par défaut
        Noeud(QString cheminRelatif); // construit un nœud
        Noeud(Voxel &boite, QString cheminRelatif); // construit un noeud en lui associant un Voxel
        Noeud(const Noeud &modele); // constructeur de recopie
        ~Noeud(); // destructeur

        /* Les fonctions de requête */
        virtual QVector<Point> requete(const Point &centre, double distance) const =0; // renvoie tous les points de tous les enfants se trouvant dans le voisinage
        virtual QVector<Point> requete(const Voxel &conteneur) const =0; // renvoie tous les points de tous les enfants contenus dans le conteneur

        /* Accesseurs et mutateurs */
        Voxel getVoxel() const;
        void setVoxel(const Voxel &boite);
        Voxel calculerVoxel();

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

    protected:
        Voxel m_boite;
        Noeud *m_enfants; // le tableau des enfants
        long m_nb_enfants; // sa taille
        QDir m_dossier; // le dossier du nœud
        Fichier m_fichier; // le fichier associé, si le noeud est terminal
        bool m_terminal; // vrai si le noeud est terminal
    private:
};

#endif // NOEUD_H

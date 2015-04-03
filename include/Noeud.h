#ifndef NOEUD_H
#define NOEUD_H

#include "include/Point.h"
#include "include/Voxel.h"
#include "include/Fichier.h"
#include <exception>

class ErreurAffectationTerminal : public std::runtime_error {
    const char* what() const {
        return "Vous avez essayé d'affecter un noeud comme enfant d'un noeud terminal.";
    }
} termAffectErreur;

class ErreurAffectationIntermediaire : public std::runtime_error {
    const char* what() const {
        return "Vous avez essayé d'affecter une feuille comme enfant d'un noeud non terminal.";
    }
} intermedAffectErreur;

class ErreurAccesTerminal : public std::runtime_error {
    const char* what() const {
        return "Vous avez essayé de récupérer une feuille alors que le noeud n'est pas terminal.";
    }
} termAccesErreur;

class ErreurAccesIntermediaire : public std::runtime_error {
    const char* what() const {
        return "Vous avez essayé de récupérer un noeud intermédiaire alors que le noeud est terminal.";
    }
} intermedAccesErreur;

class Noeud
{
    public:
        virtual Noeud(); // construit un noeud normal
        virtual Noeud(bool terminal = false); // construit un noeud basique et éventuellement terminal (constitué de fichiers (feuilles))
        virtual Noeud(Voxel &boite, bool terminal = false); // construit un noeud terminal (ou non) en lui affectant une boîte englobante.
        virtual Noeud(const Noeud &modele); // constructeur de recopie
        ~Noeud(); // destructeur

        /* Les fonctions de requête */
        virtual Point* requete(const Point &centre, double distance) const; // renvoie tous les points de tous les enfants se trouvant dans le voisinage
        virtual Point* requete(const Voxel &conteneur) const; // renvoie tous les points de tous les enfants contenus dans le conteneur

        /* Accesseurs et mutateurs */
        Noeud& getFils(long pos) const throw intermedAccesErreur; // retourne le pos-ième enfant si c'est un noeud
        Fichier& getFeuille(long pos) const throw termAccesErreur; // retourne le pos-ième enfant si c'est une feuille
        long getTailleEnfants() const; // renvoie la longueur du tableau d'enfants
        void setEnfant(long pos, Noeud &noeud) throw termAffectErreur; // remplace le pos-ième enfant par "noeud"
        void setEnfant(long pos, Fichier &feuille) throw intermedAffectErreur; // remplace le pos-ième enfant par "feuille"
        const NoeudSelonProfondeur* getEnfants() const; // retourne le tableau d'enfants (pourquoi faire ?)
        void setEnfants(NoeudSelonProfondeur enfants[], long taille, bool terminal); // remplace le tableau d'enfants (DANGEREUX !)
        Voxel getVoxel() const; // retourne la boîte englobante
        void setVoxel(Voxel &v); // définit la boîte englobante
        bool est_terminal() const; // (accesseur) renvoie vrai si le noeud est terminal (composé de feuilles = fichiers)

        union NoeudSelonProfondeur {
            Noeud *fils;
            Fichier *feuille;
        };

    protected:
    private:
        NoeudSelonProfondeur m_enfants;
        long m_taille_enfants;
        Voxel m_boite;
        bool m_terminal;
};

#endif // NOEUD_H

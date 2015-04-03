#ifndef NOEUDKD_H
#define NOEUDKD_H

#include <include/Noeud.h>
#include "Fichier.h"


class NoeudKd : public Noeud
{
    public:
        NoeudKd(); // construit un noeud normal
        NoeudKd(bool terminal = false); // construit un noeud terminal
        NoeudKd(Voxel &boite, bool terminal = false); // construit un noeud terminal en lui affectant un voxel
        NoeudKd(const NoeudKd &modele); // constructeur de recopie

        /* Les fonctions de requête */
        Point* requete(const Point &centre, double distance) const; // renvoie tous les points de tous les enfants se trouvant dans le voisinage
        Point* requete(const Voxel &conteneur) const; // renvoie tous les points de tous les enfants contenus dans le conteneur

        union NoeudSelonProfondeur {
            NoeudKd *fils;
            Fichier *feuille;
        };

        void setEnfant(long pos, NoeudKd &noeud) throw termAffectErreur; // remplace le pos-ième enfant par "noeud"
    protected:
    private:
};

#endif // NOEUDKD_H

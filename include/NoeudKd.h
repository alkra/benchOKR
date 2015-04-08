#ifndef NOEUDKD_H
#define NOEUDKD_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe NoeudKd. */

#include <../include/Noeud.h>
#include "Fichier.h"


class NoeudKd : public Noeud
{
    public:
        NoeudKd(); // construit un noeud normal
        NoeudKd(bool terminal); // construit un noeud terminal
        NoeudKd(Voxel &boite, bool terminal = false); // construit un noeud terminal en lui affectant un voxel
        NoeudKd(const NoeudKd &modele); // constructeur de recopie
        ~NoeudKd(); // destructeur

        /* Les fonctions de requête */
        Point* requete(const Point &centre, double distance) const; // renvoie tous les points de tous les enfants se trouvant dans le voisinage
        Point* requete(const Voxel &conteneur) const; // renvoie tous les points de tous les enfants contenus dans le conteneur

        union NoeudSelonProfondeur {
            NoeudKd *fils;
            Fichier *feuille;
        };

        void setEnfant(long pos, NoeudKd &noeud) throw(ErreurAffectationTerminal); // remplace le pos-ième enfant par "noeud"
    protected:
    private:
};

#endif // NOEUDKD_H

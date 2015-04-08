#ifndef NOEUDR_H
#define NOEUDR_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe NoeudR */

#include "Noeud.h"
#include "Fichier.h"


class NoeudR : public Noeud
{
    public:
        NoeudR(); // construit un noeud normal
        NoeudR(bool terminal); // construit un noeud terminal
        NoeudR(Voxel &boite, bool terminal = false);
        NoeudR(const NoeudR &modele); // constructeur de recopie

        /* Les fonctions de requête */
        Point* requete(const Point &centre, double distance) const; // renvoie tous les points de tous les enfants se trouvant dans le voisinage
        Point* requete(const Voxel &conteneur) const; // renvoie tous les points de tous les enfants contenus dans le conteneur

        void setEnfant(long pos, NoeudR &noeud)
            throw(ErreurAffectationTerminal); // remplace le pos-ième enfant par "noeud"

        const int MAX_FILS = 5;
        const int MAX_PAGES = 5;
    protected:
    private:
};
#endif // NOEUDR_H

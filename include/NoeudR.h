#ifndef NOEUDR_H
#define NOEUDR_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe NoeudR */

#include "../include/Noeud.h"
#include "../include/Fichier.h"

#include <vector>


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

        union NoeudSelonProfondeur {
            NoeudR *fils;
            Fichier *feuille;
        };

        const int MAX_FILS = 5;
        const int MAX_PAGES = 5;
    protected:
        std::vector<Point> requeteV(const Point &centre, double distance) const;
        std::vector<Point> requeteV(const Voxel &conteneur) const;
    private:
};
#endif // NOEUDR_H

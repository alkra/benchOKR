#ifndef NOEUDOCTREE_H
#define NOEUDOCTREE_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe NoeudOctree. */

#include "Noeud.h"
#include "Fichier.h"


class NoeudOctree : public Noeud
{
    public:
        NoeudOctree(); // construit un noeud normal
        NoeudOctree(bool terminal); // construit un noeud terminal
        NoeudOctree(Voxel &boite, bool terminal = false);
        NoeudOctree(const NoeudOctree &modele); // constructeur de recopie

        /* Les fonctions de requête */
        Point* requete(const Point &centre, double distance) const; // renvoie tous les points de tous les enfants se trouvant dans le voisinage
        Point* requete(const Voxel &conteneur) const; // renvoie tous les points de tous les enfants contenus dans le conteneur

        union NoeudSelonProfondeur {
            NoeudOctree *fils;
            Fichier *feuille;
        };

        void setEnfant(long pos, NoeudOctree &noeud) throw(ErreurAffectationTerminal); // remplace le pos-ième enfant par "noeud"
    protected:
    private:
};

#endif // NOEUDOCTREE_H

#ifndef NOEUDOCTREE_H
#define NOEUDOCTREE_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe NoeudOctree. */

#include "../include/Noeud.h"
#include "../include/Fichier.h"

#define getEnfant(pos) getEnfant<NoeudOctree>(pos)
#define supprimerEnfant(pos) supprimerEnfant<NoeudOctree>(pos)

class NoeudOctree : public Noeud<NoeudOctree, 8>
{
    public:
        NoeudOctree(); // construit un noeud normal
        NoeudOctree(const NoeudOctree &modele); // constructeur de recopie

        /* Les fonctions de requête */
        QVector<Point> requete(const Point &centre, double distance) const; // renvoie tous les points de tous les enfants se trouvant dans le voisinage
        QVector<Point> requete(const Voxel &conteneur) const; // renvoie tous les points de tous les enfants contenus dans le conteneur
    protected:
    private:
};

#endif // NOEUDOCTREE_H

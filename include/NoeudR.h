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

#define RTREE_MAX_ENFANTS 5

class NoeudR : public Noeud<NoeudR, RTREE_MAX_ENFANTS>
{
    public:
        NoeudR(); // construit un noeud normal
        NoeudR(const NoeudR & modele);

        /* Les fonctions de requête */
        QVector<Point> requete(const Point &centre, double distance) const; // renvoie tous les points de tous les enfants se trouvant dans le voisinage
        QVector<Point> requete(const Voxel &conteneur) const; // renvoie tous les points de tous les enfants contenus dans le conteneur
    protected:
    private:
};
#endif // NOEUDR_H

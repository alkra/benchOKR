#ifndef NOEUDKD_H
#define NOEUDKD_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe NoeudKd. */


#include "../include/Noeud.h"
#include "../include/Fichier.h"


class NoeudKd : public Noeud<NoeudKd, 2>
{
    public:
        NoeudKd(); // construit un noeud normal
        ~NoeudKd(); // destructeur

#define getEnfant(pos) getEnfant<NoeudKd>(pos)
#define supprimerEnfant(pos) supprimerEnfant<NoeudKd>(pos)

        /* Les fonctions de requête */
        QVector<Point> requete(const Point &centre, double distance) const; // renvoie tous les points de tous les enfants se trouvant dans le voisinage
        QVector<Point> requete(const Voxel &conteneur) const; // renvoie tous les points de tous les enfants contenus dans le conteneur
    protected:
    private:
};

#endif // NOEUDKD_H

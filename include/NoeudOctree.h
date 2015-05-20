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


typedef struct  // on déclare ici une structure pour stocker le volume englobant
{
    Point           centre;         // Centre du volume englobant
    double          rayon;         // Rayon du volume eglobant
} Bounds;



class NoeudOctree : public Noeud<NoeudOctree, 8>
{
    public:
        bool            construire(Point **points, unsigned int count,   // nombre total de points
                                              const unsigned int threshold, // seuil d'arrêt
                                              const unsigned int maximumDepth, // profondeur de l'arbre
                                              const Bounds &bounds,           // volume englobant
                                              std::string relation,
                                              const unsigned int currentDepth = 0); // profondeur courante
        NoeudOctree(); // construit un noeud normal
        ~NoeudOctree();
        NoeudOctree(const NoeudOctree &modele); // constructeur de recopie

        /* Les fonctions de requête */
        QVector<Point> requete(const Point &centre, double distance) const; // renvoie tous les points de tous les enfants se trouvant dans le voisinage
        QVector<Point> requete(const Voxel &conteneur) const; // renvoie tous les points de tous les enfants contenus dans le conteneur
    protected:
    private:
        NoeudOctree                  *m_enfant[8]; // tableau du nombre d'octant
        unsigned int            m_pointCount; // nombre de points
        Point                   **m_points;
};

#endif // NOEUDOCTREE_H

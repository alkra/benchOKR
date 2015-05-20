#ifndef OCTREE_H
#define OCTREE_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce Point définit la classe Octree */

#include "../include/Arbre.h"
#include "../include/NoeudOctree.h"
#include "Point.h"

#define OCTREE_DOSSIER_RACINE "../Octree"

using namespace std;




class Octree : public Arbre<NoeudOctree>  // Création d'une classe Octree qui hérite de la classe Arbre
{

public:

    // fonction de rappel pour la création des Points

   // typedef bool            (*callback)(const Octree &o, void *data);

   // constructeur

    Octree();

    // destructeur
     ~Octree();
    // méthode permettant de construire l'octree
    void construire(const QString &adresse, const QString &cheminDonnees);

       bool            construire(QString adresse,   // nombre total de points
                                               const unsigned int threshold, // seuil d'arrêt
                                               const unsigned int maximumDepth, // profondeur de l'arbre           // volume englobant
                                               const unsigned int currentDepth = 0  // profondeur courante
                                           );

    // méthode permettant de construire le volume englobant

    static  const   Bounds          calcCubicBounds(const Voxel &englobant);



    // définition de la fonction qui sera rappelée pour la création des Points

    //  virtual const   bool            traverse(callback proc, void *data) const;

    // fonction de requête

    QVector<Point> requete(const Point &centre, double distance) const; // voisinage
    QVector<Point> requete(const Voxel &conteneur) const; // dans un voxel

protected:


    Point                   m_centre;
    double                 m_rayon;
private:
};

#endif // OCTREE_H

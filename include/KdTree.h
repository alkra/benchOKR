#ifndef KDTREE_H
#define KDTREE_H

/* �ENSG 2015
 * �cole nationale des sciences g�ographiques
 * 6-8 avenue Blaise Pascal
 * Cit� Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALL�E CEDEX 2
 * FRANCE */

/* Ce fichier d�finit la classe KdTree.
 * Cette classe h�rite de Arbre et repr�sente le stockage par la m�thode du
 * Kd-tree. */

#include "Arbre.h"
#include "NoeudKd.h"


class KdTree : public Arbre<NoeudKd>  // Cr�ation d'une classe KdTree qui h�rite de la classe Arbre
{
    public:
        KdTree();
        ~KdTree();

        void construire();
        QVector<Point> requete(const Point &centre, double distance) const; // voisinage
        QVector<Point> requete(const Voxel &conteneur) const; // dans un voxel
    protected:
    private:
};

#endif // KDTREE_H

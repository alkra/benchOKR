#ifndef RTREE_H
#define RTREE_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe RTree. */

#include "../include/Arbre.h"
#include "../include/NoeudR.h"
#include "../include/Point.h"

class RTree : public Arbre<NoeudR>
// Création d'une classe RTree qui hérite de la classe Arbre
{
    public:
        class FichierFermeErreur : public std::exception {
        public:
            FichierFermeErreur();
            FichierFermeErreur(Fichier *fichier);
            const char * what() const throw ();
            Fichier * getFichier() const;
        protected:
            Fichier *m_fichier;
        };

        RTree();
        RTree(char *racine);
        ~RTree();

        void construire();
        QVector<Point> requete(const Point &centre, double distance) const; // voisinage
        QVector<Point> requete(const Voxel &conteneur) const; // dans un voxel
    protected:
    private:
        bool inserer(const Point &p);
        NoeudR* choisirFeuille(const Point &point, const NoeudR *courant) const;
        bool libre(const NoeudR* feuille) const; // détermine si le fichier a de la place pour un point de plus
        NoeudR* diviserNoeud(const Point &p, NoeudR *parent);
        NoeudR* ajusterArbre(NoeudR *feuille, NoeudR *nouveau);

        char *m_cheminRacine;
        const int MAX_FICHIER = 10;
};

#endif // RTREE_H

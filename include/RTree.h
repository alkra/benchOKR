#ifndef RTREE_H
#define RTREE_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe représentant un RTree dans sa globalité. */

#include "../include/Arbre.h"
#include "../include/NoeudR.h"
#include "../include/Point.h"




/* Gestion des fichiers */
//#define WINDOWS
#ifndef WINDOWS
#define RECUP_FICHIER_SUFFIXE "~" // Suffixe des fichiers provisoires modifier.
#define FICHIER "data" // Le nom du fichier contenant les données (feuille)
#else // plus Windowsien
#define RECUP_FICHIER_SUFFIXE ".tmp"
#define FICHIER "data.txt"
#endif

#define RECUP_FICHIER_DIVISION(nom) nom + RECUP_FICHIER_SUFFIXE // Comment construire le nom du fichier/dossier de sauvegarde. Ne pas modifier

/* Petite routine d'allocation */
#define ALLOCATION(variable, typ) \
    variable = new typ;\
    if(variable == NULL) {\
        throw new PlusDeMemoire;\
    }






class RTree : public Arbre<NoeudR>
{
    public:
        RTree();
        RTree(const QString &rac);
        ~RTree();

        void construire();
        QVector<Point> requete(const Point &centre, double distance) const; // voisinage
        QVector<Point> requete(const Voxel &conteneur) const; // dans un voxel

        const int MAX_FICHIER = 10;
        const int MIN_FICHIER = 5;
    protected:
    private:
        void inserer(const Point &p);
        NoeudR *choisirFeuille(const Point &point, NoeudR *courant) const;
        bool libre(const NoeudR* feuille) const; // détermine si le fichier a de la place pour un point de plus
        void divisionQuadratiqueFichier(const Point &p, NoeudR &premier, NoeudR &deuxieme);
        NoeudR* diviserFichier(const Point &nouveauPoint, NoeudR* parent); // divise le fichier de parent pour y ajouter nouveauPoint
        NoeudR* diviserNoeud(NoeudR *enfant, NoeudR *parent); // divise parent pour ajouter nouvelEnfant
        NoeudR* ajusterArbre(NoeudR *feuille, NoeudR *nouveau);

        QString m_cheminRacine;
};

#endif // RTREE_H

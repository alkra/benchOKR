#ifndef NOEUDR_H
#define NOEUDR_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe NoeudR, éminemment récursive,
 * représentant un R-Tree. Elle est paramétrée par le nombre maximal d'enfants
 * ci-dessous :
 */
#define RTREE_MAX_ENFANTS 5


#include "../include/Noeud.h"
#include "../include/Fichier.h"





class NoeudR : public Noeud<NoeudR, RTREE_MAX_ENFANTS>
{
    public:
        /* Constructeurs */
        NoeudR(bool terminal = false); // constructeur par défaut, noeud intermédiaire
        NoeudR(NoeudR *parent, bool terminal = false); // véritable constructeur
        NoeudR(const NoeudR & modele); // constructeur de recopie
        ~NoeudR(); // destructeur



        /* Les fonctions de requête */
        QVector<Point> requete(const Point &centre, double distance) const; // renvoie tous les points de tous les enfants se trouvant dans le voisinage (appelle la fonction suivante)
        QVector<Point> requete(const Voxel &conteneur) const; // renvoie tous les points de tous les enfants contenus dans le conteneur




        /* Accesseurs et mutateurs */

        /* Pour éviter le template */
        inline NoeudR getEnfant(long pos) const
            throw(TerminalErreur, IndiceHorsDomaine) {
            return Noeud::getEnfant<NoeudR>(pos);
        }
        inline NoeudR supprimerEnfant(long pos = -1)
            throw(TerminalErreur, IndiceHorsDomaine) {
            return Noeud::supprimerEnfant<NoeudR>(pos);
        }

        /* m_parent */
        NoeudR *getParent() const;
        void setParent(NoeudR *parent);

        /* Prennent en compte le parent du noeud */
        void setEnfant(NoeudR &nouveau, long pos)
            throw(TerminalErreur, IndiceHorsDomaine);
        void ajoutEnfant(NoeudR &nouveau, long pos = -1)
            throw(TerminalErreur, IndiceHorsDomaine);



    protected:
        NoeudR *m_parent; // certains algorithmes doivent remonter l'arbre
};
#endif // NOEUDR_H

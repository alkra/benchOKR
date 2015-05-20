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
        NoeudKd(bool terminal = false); // construit un noeud par défaut
        NoeudKd(QString cheminRelatif, bool terminal = false); // construit un nœud
        NoeudKd(Voxel &boite, QString cheminRelatif, bool terminal = false); // construit un noeud en lui associant un Voxel
        NoeudKd(const NoeudKd &modele);
        virtual ~NoeudKd(); // destructeur


        /* Les fonctions de requête */
        QVector<Point> requete(const Point &centre, double distance) const; // renvoie tous les points de tous les enfants se trouvant dans le voisinage
        QVector<Point> requete(const Voxel &conteneur) const; // renvoie tous les points de tous les enfants contenus dans le conteneur

        /* Pour éviter le template */
        inline NoeudKd getEnfant(long pos) const
            throw(TerminalErreur, IndiceHorsDomaine) {
            return Noeud::getEnfant<NoeudKd>(pos);
        }
        inline NoeudKd supprimerEnfant(long pos = -1)
            throw(TerminalErreur, IndiceHorsDomaine) {
            return Noeud::supprimerEnfant<NoeudKd>(pos);
        }
    protected:
    private:
};

#endif // NOEUDKD_H

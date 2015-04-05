#ifndef FICHIER_H
#define FICHIER_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe Fichier.
 * Nous avons décidé de stocker les points dans un fichier (d'où le nom de la
 * classe) qui seront insérés aux feuilles de notre arborescence de
 * répertoires.
 * Cette classe représente un tel fichier.
 * Lors de la construction de l'arbre, on devra écrire dans ce fichier ;
 * et le lire lors des requêtes. */

/* À faire :
 *  -- Doit-on garder le fichier ouvert (i.e. l'ouvrir dans le constructeur
 *     et le fermer dans le destructeur), permettre de l'ouvrir et de le
 *     fermer manuellement, ou bien l'ouvrir et le fermer à chaque accès ?
 *  -- Si on le garde ouvert, sous quelle forme le stocke-t-on (i/ostream) ?
 *  -- Implémenter les méthodes */

#include "Point.h"
#include "Voxel.h"
#include "Noeud.h"
#include <QString>

class Fichier
{
    public:
        Fichier(QString chemin); // constructeur
        ~Fichier(); // destructeur

        Point getPoint(long pos); // renvoie le pos-ième point du fichier

        /* Les fonctions de requête */
        Point* requete(const Point &centre, double distance) const; // renvoie tous les points du fichier se trouvant à une distance 'distance' de 'centre'
        Point* requete(const Voxel &conteneur) const; // // renvoie tous les points du fichier contenus dans 'conteneur'

        /* Accesseurs et mutateurs (1 par attribut) */
        // iofstream getFichier() const;
        // void setFichier(iofstream f);
    protected:
    private:
        /* Une feuille est associée à un fichier : */
        // iofstream *fichier;
};

#endif // FICHIER_H

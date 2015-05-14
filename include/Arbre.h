#ifndef ARBRE_H
#define ARBRE_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier déclare la classe abstraite Arbre.
 * Cette classe sera héritée par nos trois méthodes de construction.
 * Elle représente l'arbre en train d'être construit. */

#include "../include/Noeud.h"
#include "../include/Point.h"
#include "../include/Voxel.h"
#include <QString>

template <class Nd>
class Arbre  // déclaration de la classe Abstraite Arbre
{

    // méthodes de la classe Arbre
    public:
        /* Une méthode virtuelle est une méthode dont on ne donne pas le code. (cf. Arbre.cpp)
         * On s'en sert pour définir une simple interface.
         * Conséquence : on ne peut pas les appeler depuis un objet instancié.
         * Pour être utilisables, on doit hériter la classe et les redéfinir.
         *
         * Ici, le constructeur est virtuel, donc on ne pourra même pas instancier un objet de type Arbre.
         */

        Arbre(); // constructeur d'Arbre

        /*création de fonction virtuelle pour rendre la classe abstraite pour la résolution dynamique des liens:
        2 possibilités s'offrents à nous
        -utilisation de pointeur ou référence
        - utilisation de fonction virtuelle comme c'est le cas ici
        */ // (Alban) euh bon...

        virtual void construire(const QString& racine, const QString& cheminDonnes) =0;
        virtual QVector<Point> requete(const Point &centre, double distance) const =0; // voisinage
        virtual QVector<Point> requete(const Voxel &conteneur) const =0; // dans un voxel

        /* Accesseurs et mutateurs */
        Nd* getRacine() const; // renvoie un pointeur vers la racine
        void setRacine(Nd *nouvelle); // dangereux, on n'a pas à l'utiliser

    // attributs de la classe arbre
    protected:
        Nd* racine; // Pointe vers le début de l'arbre

    private:

};

#include "../src/Arbre.cpp" // Pour pouvoir accéder aux fonctions templatées

#endif // ARBRE_H

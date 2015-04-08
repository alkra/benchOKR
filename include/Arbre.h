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

#include "Noeud.h"
#include "Point.h"
#include "Voxel.h"

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

        virtual void construire() =0;
        virtual Point* requete(const Point &centre, double distance) const =0; // voisinage
        virtual Point* requete(const Voxel &conteneur) const =0; // dans un voxel

        /* Accesseurs et mutateurs */
        Noeud* getRacine() const; // renvoie un pointeur vers la racine
        void setRacine(Noeud* nouvelle); // dangereux, on n'a pas à l'utiliser

    // attributs de la classe arbre
    protected:
        Noeud* racine; // Pointe vers le début de l'arbre

    private:

};

#endif // ARBRE_H

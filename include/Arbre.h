#ifndef ARBRE_H
#define ARBRE_H

#include "include/Noeud.h"
#include "include/Point.h"
#include "include/Point.h"
#include "include/Voxel.h"

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

        virtual Arbre(); // constructeur d'Arbre
        virtual ~Arbre(); // destructeur d'Arbre

        /*création de fonction virtuelle pour rendre la classe abstraite pour la résolution dynamique des liens:
        2 possibilités s'offrents à nous
        -utilisation de pointeur ou référence
        - utilisation de fonction virtuelle comme c'est le cas ici
        */ // (Alban) euh bon...

        virtual void construire();
        virtual Point* requete(const Point &centre, double distance) const; // voisinage
        virtual Point* requete(const Voxel &conteneur) const; // dans un voxel

        /* Accesseurs et mutateurs */
        Noeud* getRacine() const; // renvoie un pointeur vers la racine
        void setRacine(Noeud* nouvelle); // dangereux, on n'a pas à l'utiliser

    // attributs de la classe arbre
    protected:
        Noeud* racine;

    private:






};

#endif // ARBRE_H

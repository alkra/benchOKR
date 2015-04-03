#ifndef ARBRE_H
#define ARBRE_H

#include "include/Noeud.h"
#include "include/Point.h"
#include "include/Point.h"
#include "include/Voxel.h"

class Arbre  // d�claration de la classe Abstraite Arbre
{

    // m�thodes de la classe Arbre
    public:
        /* Une m�thode virtuelle est une m�thode dont on ne donne pas le code. (cf. Arbre.cpp)
         * On s'en sert pour d�finir une simple interface.
         * Cons�quence : on ne peut pas les appeler depuis un objet instanci�.
         * Pour �tre utilisables, on doit h�riter la classe et les red�finir.
         *
         * Ici, le constructeur est virtuel, donc on ne pourra m�me pas instancier un objet de type Arbre.
         */

        virtual Arbre(); // constructeur d'Arbre
        virtual ~Arbre(); // destructeur d'Arbre

        /*cr�ation de fonction virtuelle pour rendre la classe abstraite pour la r�solution dynamique des liens:
        2 possibilit�s s'offrents � nous
        -utilisation de pointeur ou r�f�rence
        - utilisation de fonction virtuelle comme c'est le cas ici
        */ // (Alban) euh bon...

        virtual void construire();
        virtual Point* requete(const Point &centre, double distance) const; // voisinage
        virtual Point* requete(const Voxel &conteneur) const; // dans un voxel

        /* Accesseurs et mutateurs */
        Noeud* getRacine() const; // renvoie un pointeur vers la racine
        void setRacine(Noeud* nouvelle); // dangereux, on n'a pas � l'utiliser

    // attributs de la classe arbre
    protected:
        Noeud* racine;

    private:






};

#endif // ARBRE_H

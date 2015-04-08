#ifndef ARBRE_H
#define ARBRE_H

/* �ENSG 2015
 * �cole nationale des sciences g�ographiques
 * 6-8 avenue Blaise Pascal
 * Cit� Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALL�E CEDEX 2
 * FRANCE */

/* Ce fichier d�clare la classe abstraite Arbre.
 * Cette classe sera h�rit�e par nos trois m�thodes de construction.
 * Elle repr�sente l'arbre en train d'�tre construit. */

#include "Noeud.h"
#include "Point.h"
#include "Voxel.h"

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

        Arbre(); // constructeur d'Arbre

        /*cr�ation de fonction virtuelle pour rendre la classe abstraite pour la r�solution dynamique des liens:
        2 possibilit�s s'offrents � nous
        -utilisation de pointeur ou r�f�rence
        - utilisation de fonction virtuelle comme c'est le cas ici
        */ // (Alban) euh bon...

        virtual void construire() =0;
        virtual Point* requete(const Point &centre, double distance) const =0; // voisinage
        virtual Point* requete(const Voxel &conteneur) const =0; // dans un voxel

        /* Accesseurs et mutateurs */
        Noeud* getRacine() const; // renvoie un pointeur vers la racine
        void setRacine(Noeud* nouvelle); // dangereux, on n'a pas � l'utiliser

    // attributs de la classe arbre
    protected:
        Noeud* racine; // Pointe vers le d�but de l'arbre

    private:

};

#endif // ARBRE_H

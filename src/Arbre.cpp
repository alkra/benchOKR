/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe Arbre. */

#include "include/Arbre.h"

Noeud* Arbre::getRacine() const {
    return racine;
}

void Arbre::setRacine(Noeud* nouvelle) {
    racine = nouvelle;
}


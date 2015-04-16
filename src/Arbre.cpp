/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

#ifndef ARBRE_CPP
#define ARBRE_CPP

/* Ce fichier contient l'implémentation des méthodes de la classe Arbre. */

#include "../include/Arbre.h"

template <class Nd> Arbre<Nd>::Arbre() : racine(NULL) {
}

template <class Nd> Nd* Arbre<Nd>::getRacine() const {
    return racine;
}

template <class Nd> void Arbre<Nd>::setRacine(Nd* nouvelle) {
    racine = nouvelle;
}

#endif // ARBRE_CPP


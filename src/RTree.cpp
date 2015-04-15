/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe RTree. */

#include "../include/RTree.h"

#include <iostream>

RTree::RTree() : m_cheminRacine("") {
}

RTree::RTree(char *racine) : m_cheminRacine(racine)
{
    //ctor
}

RTree::~RTree()
{
    delete[] m_cheminRacine;
    //dtor
}



void RTree::construire() {
    // Code spécifique au kd-tree
}

QVector<Point> RTree::requete(const Point &centre, double distance) const {
    return racine->requete(centre, distance);
}

QVector<Point> RTree::requete(const Voxel &conteneur) const {
    return racine->requete(conteneur);
}

bool RTree::inserer(const Point &p) { // Gut84 : algorithm Insert
    NoeudR *parent = NULL;
    long lieu = choisirFeuille(p, racine, parent); // Gut84 : I1
    Fichier& feuille = parent->getFeuille(lieu);

    if(!feuille.ouvrir()) {
        std::cerr << "Insertion du point " << p.toQString() << " a échoué." << endl;
        std::cerr << "Impossible d'ouvrir le fichier de destionation :" << endl;
        std::cerr << feuille.getFichier().fileName() << endl;
        return false;
    }

    /* Gut84 : I2 */
    if(libre(feuille)) {
        feuille.ajoutPoint(p);
    } else {
        Fichier *nouveau = diviserNoeud(p, parent, lieu);

        /* Gut84 : I3 */
        NoeudR *deuxiemeRacine = ajusterArbre(parent, nouveau);

        /* Gut84 : I4 */
        if(deuxiemeRacine) {
            NoeudR nouvelleRacine;
            nouvelleRacine.setEnfant(0, racine);
            nouvelleRacine.setEnfant(1, *deuxiemeRacine);
        }
    }
}

/* Gut84 : ChooseLeaf */
long RTree::choisirFeuille(const Point &point, NoeudR* courant, NoeudR *parent) {
    if(courant->est_terminal()) { // Gut84 : CL2
        parent = courant;
        return choisirSousArbre;
    }
    else { // Gut84 : CL3
        Voxel *courant = NULL, *nouveau = NULL;
        long arret =
        for(long i = 0 ; i < NoeudR::MAX_FILS)
    }
}

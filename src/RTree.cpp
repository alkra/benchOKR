/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe RTree. */

#include "../include/RTree.h"

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

RTree::FichierFermeErreur::FichierFermeErreur() : m_fichier(NULL) {}
RTree::FichierFermeErreur::FichierFermeErreur(Fichier *fichier) : m_fichier(fichier) {}
Fichier* RTree::FichierFermeErreur::getFichier() const {
    return m_fichier;
}
const char * RTree::FichierFermeErreur::what() const throw() {
    QString message(
                QString("Le fichier%1 est fermé.").arg(
                    m_fichier == NULL ?
                        QString() :
                        QString(" %1").arg(
                            m_fichier->getFichier().fileName()
                            )
                        )
                );
    QByteArray m = message.toLocal8Bit();
    return m.data();
}

bool RTree::inserer(const Point &p) { // Gut84 : algorithm Insert
    NoeudR *parent = choisirFeuille(p, racine); // Gut84 : I1
    Fichier& f = *(parent->getFichier());

    if(!f.estOuvert()) {
        throw new FichierFermeErreur;
    }

    /* Gut84 : I2 */
    if(libre(parent)) {
        f.ajoutPoint(p);
    } else {
        NoeudR *nouveau = diviserNoeud(p, parent);

        /* Gut84 : I3 */
        NoeudR *deuxiemeRacine = ajusterArbre(parent, nouveau);

        /* Gut84 : I4 */
        if(deuxiemeRacine) {
            NoeudR *nouvelleRacine = new NoeudR();
            nouvelleRacine->ajoutEnfant(*racine);
            nouvelleRacine->ajoutEnfant(*deuxiemeRacine);
            racine = nouvelleRacine;
        }
    }
}

/* Gut84 : ChooseLeaf */
NoeudR *RTree::choisirFeuille(const Point &point, const NoeudR *courant) const {
    // non implémenté
    return NULL;
}

bool RTree::libre(const NoeudR *feuille) const {
    // non implémenté
    return true;
}

NoeudR *RTree::diviserNoeud(const Point &p, NoeudR *parent) {
    // non implémenté
    return NULL;
}

NoeudR* RTree::ajusterArbre(NoeudR *feuille, NoeudR *nouveau) {
    // non implémenté
    return NULL;
}

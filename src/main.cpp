/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

#include <iostream>
#include<string>
using namespace std;

#include "../include/RTree.h"


int main()
{
    QDir racine("../rtree");
    racine.removeRecursively();

    RTree *r = NULL;
    try {
        ALLOCATION(r, RTree(racine.absoluteFilePath("0")))
    } catch(PlusDeMemoire m) {
        qFatal("Plus de mémoire disponible.");
    } catch(int e) {
        if(e == 2) {
            qFatal("Impossible d'ouvrir le fichier de données à la racine.");
        } else {
            qFatal(QString("Erreur %1").arg(e).toLocal8Bit().data());
        }
    }

    r->construire();
}

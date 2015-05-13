/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

#include <QCoreApplication>
#include <iostream>
#include<string>
using namespace std;


#include "../include/RTree.h"
#include "../include/Point.h"
#include "../include/Octree.h"
#include "../include/NoeudOctree.h"
#include"../include/Point3D.h"
#include"../include/Fichier.h"
#include"..//include/Arbre.h"
#include <QDebug>
#include<QString>

#define ARAIGNEE_PLY "C:/code04Mai2015/constructionOctree4Mai/araignee.ply"
#define SALAMANDRE_TXT "../donneeTestDIAS/SalamandreCloud.txt"

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

    //Fichier util;
    // Ouverture du fichier

    //util.ouvrir("C:/code04Mai2015/constructionOctree4Mai/araignee.ply", QIODevice::ReadOnly | QIODevice::Text);
    //util.ouvrir("E:/Git/ProjetDeveloppement/jeuTest/Salamandre.ply", QIODevice::ReadOnly | QIODevice::Text);





    // renvoyer la liste des points
    //Point **points = util.getPoints();
    // compter le nombre de points

    //int nbrePts = util.getNbPoints();

    //qDebug()<<nbrePts;

//    QString ligneLue;

//    ligneLue=points.at(10)->toQString();

//    qDebug()<< ligneLue;


    Octree monArbre;
    QString chemin=SALAMANDRE_TXT;

     //monArbre.construire(chemin,500,4,0);


    //test.construire(points,nbrePts,500,4,b,0);
    return 0;
}


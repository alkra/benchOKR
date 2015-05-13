/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

#include <iostream>
using namespace std;

#include "../include/KdTree.h"
#include "../include/NoeudKd.h"
#include "../include/RTree.h"
#include "../include/Octree.h"
#include "../include/NoeudOctree.h"

#define ARAIGNEE_PLY "C:/code04Mai2015/constructionOctree4Mai/araignee.ply"
#define SALAMANDRE_TXT "../donneeTestDIAS/SalamandreCloud.txt"


int main(int argc, char *argv[])
{
    /*NoeudKd* p11;
    KdTree p;
    p11=p.construire1();

    string* path1;
    path1=new string[14];
    Voxel* voxel;
    voxel=new Voxel[14];


    //p.construire1();


    Point3D point1(1.63704,2.8783,1.74817);
    Point3D point2(12,2,5);
    double a1,a2,a3,b1,b2,b3;

    int j=0;
    for (int i=0;i<14;i++)
    {
        path1[i]=p11[i].getpath();
        cout<<"path :"<<path1[i]<<endl;
        a1=p11[i].getVoxel().getFin().getX();//voxels extrait de la fonction construire
        a2=p11[i].getVoxel().getFin().getY();
        a3=p11[i].getVoxel().getFin().getZ();
        cout<<"a1:"<<a1<<"a2:"<<a2<<"a3:"<<a3<<endl;
        cout<<"point entree:"<<point1.getX()<<endl;
        if((point1.getX()<=a1) && (point1.getY()<=a2) && (point1.getZ()<=a3))
        {
            j++;
        }
    }

    cout<<"j:"<<j<<endl;
    if (j==0){
        // déclencher une exception par pointeur
        cout<<"entrer une autre valeur"<<endl;
    }
    else{

        if(j>6)
        {
            cout<<path1[j-1]<<endl;
            //lire les points du path j
        }
        else{
            for(int k=6;k<14;k++)
            {
                if(path1[k].compare(0,path1[j-1].length(), path1[j-1]) == 0)//path[i] est le plus long .
                {
                    // lire lies fichier du path k path[k];
                }
            }

        }

}
    //lire les point du path[j] telque les point
    //sont compris entre les points en entré
    //else lire les point
*/

    /*QDir racine("../rtree");
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

    r->construire();*/

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

     monArbre.construire(chemin,500,4,0);


    //test.construire(points,nbrePts,500,4,b,0);
    return 0;

}

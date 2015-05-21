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

/* Chemin vers les données */
#define ARAIGNEE_PLY "C:/code04Mai2015/constructionOctree4Mai/araignee.ply"
#define SALAMANDRE_TXT "../donneeTestDIAS/SalamandreCloud.txt"

/* Type de construction attendue */
#define CONSTRUIRE_KD
//#define CONSTRUIRE_OCTREE
//#define CONSTRUIRE_RTREE


int main(int argc, char *argv[])
{
#ifdef CONSTRUIRE_KD
    /*NoeudKd* p11;*/
    NoeudKd* kdDecoupage;
    KdTree p;
    NoeudKd ndkd;
   int niveau=3;
    kdDecoupage=p.construire1(QString("E:/Test/Z/Z1"),QString("E:/araignee.ply"),niveau);

    Point3D point1(2.6365,3.01941,1.99355);

    Point3D point2(2,3,2);
    Point3D point3;
    Point3D point4;

    Voxel intersect;
    Voxel v,voxel;
    v.setDebut(point1);
    v.setFin(point2);
    //intersect.setDebut(point3);
    //intersect.setFin(point4);
    int NiveauArray=0;
    for(int i5=1;i5<niveau+1;i5++){
    NiveauArray=NiveauArray+pow(2,i5);
    }

    int j=0;

    for (int i=0;i<=NiveauArray;i++)
    {


        cout<<"path :"<<kdDecoupage[i].getDossier().absolutePath().toLocal8Bit().data()<<endl;
        point3.setX(kdDecoupage[i].getVoxel().getDebut().getX());
        point3.setY(kdDecoupage[i].getVoxel().getDebut().getY());
        point3.setZ(kdDecoupage[i].getVoxel().getDebut().getZ());
        point4.setX(kdDecoupage[i].getVoxel().getFin().getX());
        point4.setY(kdDecoupage[i].getVoxel().getFin().getY());
        point4.setZ(kdDecoupage[i].getVoxel().getFin().getZ());

       intersect.setDebut(point3);
       intersect.setFin(point4);
      /* cout<<"poin1:"<<intersect.getDebut().getX()<<" ";
       cout<<intersect.getDebut().getY()<<" ";
       cout<<intersect.getDebut().getZ()<<" ";
       cout<<"point2:"<<intersect.getFin().getX()<<" ";
       cout<<intersect.getFin().getY()<<" ";
       cout<<intersect.getFin().getZ()<<" ";*/

        if (Voxel::intersecte(intersect,v)) //(intersect.intersecte(point1))//
        {
                j=i;

        }

    }
    cout<<"/n"<<j<<" "<<kdDecoupage[j].getDossier().absolutePath().toLocal8Bit().data()<<"hhhhhhhh"<<endl;

#endif


#ifdef CONSTRUIRE_RTREE
    QDir racine("../rtree");
    racine.removeRecursively();
    RTree r;
    r.construire(racine.absoluteFilePath("0"), SALAMANDRE_TXT);
#endif


#ifdef CONSTRUIRE_OCTREE
    Octree monArbre;
    QString chemin=SALAMANDRE_TXT;

    monArbre.construire(chemin,500,4,0);
#endif


    return 0;
}

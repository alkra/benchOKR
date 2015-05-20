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
#include "../include/simpleOctree.h"

/* Chemin vers les données */
#define ARAIGNEE_PLY "C:/code04Mai2015/constructionOctree4Mai/araignee.ply"
#define SALAMANDRE_TXT "../donneeTestDIAS/SalamandreCloud.txt"

/* Type de construction attendue */
//#define CONSTRUIRE_KD
//#define CONSTRUIRE_OCTREE
//#define CONSTRUIRE_RTREE
#define SIMPLE_OCTREE

int main(int argc, char *argv[])
{

#ifdef SIMPLE_OCTREE
    /* Code récupéré sur https://github.com/brandonpelfrey/SimpleOctree/ */
    brandonpelfrey::Octree *oct = NULL;
    init();
    testNaive();
    testOctree();
#endif

#ifdef CONSTRUIRE_KD
    /*NoeudKd* p11;*/
    KdTree p;
    p.construire("kd/", SALAMANDRE_TXT);

    /*string* path1;
    path1=new string[14];
    Voxel* voxel;
    voxel=new Voxel[14];

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
    }*/
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

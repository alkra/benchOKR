/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */


// element de la camera
#include <QCoreApplication>

#include <QApplication>

// element de la camera

#include <iostream>
#include<string>



using namespace std;

#include "../include/KdTree.h"
#include "../include/NoeudKd.h"
#include "../include/RTree.h"
#include "../include/Octree.h"
#include "../include/NoeudOctree.h"
#include "../include/simpleOctree.h"
#include"../include/Point3D.h"
#include"../include/Fichier.h"
#include"../include/simpleViewer.h"
#include"..//include/Arbre.h"
#include <QDebug>
#include<QString>

#define ARAIGNEE_PLY "../donneeTestDIAS/araignee.ply"
#define POINT3D "C:/code04Mai2015/constructionOctree4Mai/Point3D_v3.txt"
#define SALAMANDRE_TXT "C:/code04Mai2015/constructionOctree4Mai/SalamandreCloud.txt"


/* Type de construction attendue */
//#define CONSTRUIRE_KD
//#define CONSTRUIRE_OCTREE
//#define CONSTRUIRE_RTREE
//#define SIMPLE_OCTREE





using namespace std;
int main(int argc, char** argv)
{
    // Read command lines arguments.
    QApplication application(argc,argv);
    qDebug() << qApp;


    // Lecture de nuage de Point3D
    
//     Point3D point;
//      point.load(nuage, cheminNuagePoint.c_str());
      


    // Instantiate the viewer.
    //Viewer viewer;

    //viewer.m_afficher = new Point*[4];
    //viewer.m_tailleAfficher = 4;
    //viewer.m_afficher[0] = new Point(0.5f, 0.5f, 0.5f);
    //viewer.m_afficher[1] = new Point(-0.5f, 0.5f, 0.5f);
    //viewer.m_afficher[2] = new Point(-0.5f, -0.5f, 0.5f);
    //viewer.m_afficher[3] = new Point(0.5f, -0.5f, 0.5f);

    //Fichier donnees(ARAIGNEE_PLY);
    //Point ** pointsDonnees = donnees.getPoints();
    //int nbPoints = donnees.getNbPoints();


#ifdef SIMPLE_OCTREE
    /* Code récupéré sur https://github.com/brandonpelfrey/SimpleOctree/ */
    // Create a new Octree centered at the origin
    // with physical dimension 2x2x2
    Vec3 qmin, qmax;
    std::vector<Vec3> points;
    Point * p = NULL;
    {
        for(int i=0 ; i < nbPoints ; i++) {
            p = pointsDonnees[i];
            if(p->getX() < qmin.x) qmin.x = p->getX();
            if(p->getY() < qmin.y) qmin.y = p->getY();
            if(p->getZ() < qmin.z) qmin.z = p->getZ();
            if(p->getX() > qmax.x) qmax.x = p->getX();
            if(p->getY() > qmax.y) qmax.y = p->getY();
            if(p->getZ() > qmax.z) qmax.z = p->getZ();
            points.push_back(Vec3(p->getX(), p->getY(), p->getZ()));
        }
        qDebug() << nbPoints << " lus, " << points.size() << " convertis.";
    }

    Vec3 origin((qmax.x + qmin.x) /2, (qmax.y + qmin.y)/2, (qmax.z + qmin.z)/2);
    Vec3 half((qmax.x + qmin.x) /2, (qmax.y + qmin.y)/2, (qmax.z + qmin.z)/2);
    brandonpelfrey::Octree *octree = new brandonpelfrey::Octree(origin, half);
    OctreePoint *octreePoints = NULL;
    init(octree, octreePoints, points, qmin, qmax);
    qDebug() << "Octree construit";
    qDebug() << "Requête entre (2, 2, 2) et (3, 3, 3)";
    qmin.x = 2; qmin.y = 2; qmin.z = 2;
    qmax.x = 3; qmax.y = 3; qmax.z = 3;
    testNaive(points, qmin, qmax);
    testOctree(octree, qmin, qmax);
#endif

    //viewer.m_tailleAfficher = nbPoints;
    //
    //for(int i = 0 ; i < viewer.m_tailleAfficher ; i++) {
    //    pointsDonnees[i]->setX(pointsDonnees[i]->getX() /10);
    //    pointsDonnees[i]->setY(pointsDonnees[i]->getY() /10);
    //    pointsDonnees[i]->setZ(pointsDonnees[i]->getZ() /10);
    //}
    //
    //viewer.m_afficher = pointsDonnees;

    //viewer.setWindowTitle("simpleViewer");

    // Make the viewer window visible on screen.
    //viewer.show();

    // Run main loop.
    return application.exec();

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
}

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
#include "../include/mainwindow.h"
#include <QDebug>
#include<QString>

#define ARAIGNEE_PLY "../donneeTestDIAS/araignee.ply"
#define POINT3D "C:/code04Mai2015/constructionOctree4Mai/Point3D_v3.txt"
#define SALAMANDRE_TXT "../donneeTestDIAS/SalamandreCloud.txt"


/* Type de construction attendue */
//#define CONSTRUIRE_KD
//#define CONSTRUIRE_OCTREE
//#define CONSTRUIRE_RTREE
//#define SIMPLE_OCTREE





using namespace std;
int main(int argc, char** argv)
{
    double startApplication, endComputing, startResize, getNP, stopRead,
            startRead, startOpenFile, startNaiveQuery, stopNaiveQuery,
            vec3start, vec3stop, startCreateOctree, stopCreateOctree,
            startOctreeQuery, stopOctreeQuery;
    //startApplication = stopwatch2();


    // Read command lines arguments.
    QApplication application(argc,argv);
    MainWindow fenetrePrincipale(&application);
    fenetrePrincipale.show();

    // Lecture de nuage de Point3D
    
//     Point3D point;
//      point.load(nuage, cheminNuagePoint.c_str());
      


    // Instantiate the viewer.
    Viewer viewer;

    //viewer.m_afficher = new Point*[4];
    //viewer.m_tailleAfficher = 4;
    //viewer.m_afficher[0] = new Point(0.5f, 0.5f, 0.5f);
    //viewer.m_afficher[1] = new Point(-0.5f, 0.5f, 0.5f);
    //viewer.m_afficher[2] = new Point(-0.5f, -0.5f, 0.5f);
    //viewer.m_afficher[3] = new Point(0.5f, -0.5f, 0.5f);

    //startOpenFile = stopwatch2();
    //Fichier donnees(ARAIGNEE_PLY);
    //startRead = stopwatch2();
    //Point ** pointsDonnees = donnees.getPoints();
    //stopRead = stopwatch2();
    //int nbPoints = donnees.getNbPoints();
    //getNP = stopwatch2();


    //vec3start = stopwatch2();
    /* Code récupéré sur https://github.com/brandonpelfrey/SimpleOctree/ */
    // Create a new Octree centered at the origin
    // with physical dimension 2x2x2
    //Vec3 qmin(1000, 1000, 1000), qmax(-1000, -1000, -1000);
    //std::vector<Vec3> points;
    //Point * p = NULL;
    //{
    //    // Calcul du voxel englobant et conversion
    //    for(int i=0 ; i < nbPoints ; i++) {
    //        p = pointsDonnees[i];
    //        if(p->getX() < qmin.x) qmin.x = p->getX();
    //        if(p->getY() < qmin.y) qmin.y = p->getY();
    //        if(p->getZ() < qmin.z) qmin.z = p->getZ();
    //        if(p->getX() > qmax.x) qmax.x = p->getX();
    //        if(p->getY() > qmax.y) qmax.y = p->getY();
    //        if(p->getZ() > qmax.z) qmax.z = p->getZ();
    //        points.push_back(Vec3(p->getX(), p->getY(), p->getZ()));
    //    }
    //}
    //vec3stop = stopwatch2();

#ifdef SIMPLE_OCTREE
    startCreateOctree = stopwatch2();
    Vec3 origin((qmax.x + qmin.x) /2, (qmax.y + qmin.y)/2, (qmax.z + qmin.z)/2);
    Vec3 half((qmax.x - qmin.x) /2, (qmax.y - qmin.y)/2, (qmax.z - qmin.z)/2);
    qDebug() << "Origin : " << origin.x << origin.y << origin.z;
    qDebug() << "Half-width : " << half.x << half.y << half.z;
    brandonpelfrey::Octree *octree = new brandonpelfrey::Octree(origin, half);
    OctreePoint *octreePoints = NULL;
    init(octree, octreePoints, points, qmin, qmax);
    stopCreateOctree = stopwatch2();
#endif

    //viewer.setWindowTitle("simpleViewer");
    //viewer.setFPSIsDisplayed(true);
    //
    //// Make the viewer window visible on screen.
    //viewer.show();
    //
    //
    //
    ////qmin.x = -1; qmin.y = 5; qmin.z = -11;
    ////qmax.x = 0; qmax.y = 6; qmax.z = -10;
    //
    //qmin.x = 0; qmin.y = 0; qmin.z = 0;
    //qmax.x = 9; qmin.y = 9; qmin.z = 9;


#ifdef SIMPLE_OCTREE
    std::vector<OctreePoint*> champDeVision;

    startOctreeQuery = stopwatch2();
    testOctree(octree, qmin, qmax, champDeVision);
    stopOctreeQuery = stopwatch2();

    viewer.m_tailleAfficher = champDeVision.size();
    viewer.m_afficher = new Point*[viewer.m_tailleAfficher];
    Vec3 data;
    for(int i=0 ; i < viewer.m_tailleAfficher ; i++) {
        data = champDeVision[i]->getPosition();
        viewer.m_afficher[i] = new Point(data.x, data.y, data.z);
    }
#else
    //std::vector<int> champDeVision;
    //startNaiveQuery = stopwatch2();
    //testNaive(points, qmin, qmax, champDeVision);
    //stopNaiveQuery = stopwatch2();
    //
    //viewer.m_tailleAfficher = champDeVision.size();
    //Point ** affichage = new Point*[viewer.m_tailleAfficher];
    //
    //startResize = stopwatch2();
    //for(int i = 0 ; i < viewer.m_tailleAfficher ; i++) {
    //    pointsDonnees[i]->setX(pointsDonnees[i]->getX() /10);
    //    pointsDonnees[i]->setY(pointsDonnees[i]->getY() /10);
    //    pointsDonnees[i]->setZ(pointsDonnees[i]->getZ() /10);
    //}
    //for(int i = 0 ; i < viewer.m_tailleAfficher ; i++) {
    //    affichage[i] = pointsDonnees[champDeVision[i]];
    //}
    //endComputing = stopwatch2();
    //
    //viewer.m_afficher = affichage;
#endif

    //viewer.qmin = qmin;
    //viewer.qmax = qmax;
    //
    //
    //qDebug() << "Loading data";
    //qDebug() << "    Reading file in " << stopRead - startRead;
    //qDebug() << "    Total access file time : " << getNP - startOpenFile;
    //qDebug() << "    Converted " << nbPoints << " points in " << vec3stop - vec3start;
#ifdef SIMPLE_OCTREE
    //qDebug() << "    Building Octree in " << stopCreateOctree - startCreateOctree;
    //qDebug() << "Query using Octree";
    //qDebug() << "    Result : " << viewer.m_tailleAfficher << " points in " << stopOctreeQuery - startOctreeQuery;
#else
    //qDebug() << "Naive query";
    //qDebug() << "    Result in " << stopNaiveQuery - startNaiveQuery;
    //qDebug() << "    Converted " << viewer.m_tailleAfficher << "points in " << endComputing - startResize;
#endif

    /* AFFICHAGE DES BOÎTES ENGLOBANTES */

#ifdef SIMPLE_OCTREE
    // Instantiate the viewer.
    //Viewer fenetreBB;
    //fenetreBB.setWindowTitle("Centres des boîtes englobantes");
    //fenetreBB.setFPSIsDisplayed(true);

    //std::vector<Point*> a; int tailleAfficher;
    //octree->getOrigins(a, tailleAfficher);
    //
    //fenetreBB.m_tailleAfficher = tailleAfficher;
    //fenetreBB.m_afficher = new Point*[tailleAfficher];
    //for (int i = 0 ; i < tailleAfficher ; i++) {
    //    fenetreBB.m_afficher[i] = a[i];
    //}

    // Make the viewer window visible on screen.
    //fenetreBB.show();
#endif



#ifdef CONSTRUIRE_KD
    /*NoeudKd* p11;*/
    NoeudKd* kdDecoupage;
    KdTree kdtree;
    NoeudKd ndkd;
   int niveau=3;
    kdDecoupage=kdtree.construire1(QString("../kdtree/Z/Z1"),QString("../donneeTestDIAS/araignee.txt"),niveau);

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

    // Run main loop.
    int runCode = application.exec();

    //for(int i = 0 ; i < viewer.m_tailleAfficher ; i++) {
    //    delete pointsDonnees[i];
    //}
    //delete pointsDonnees;
    return runCode;
}

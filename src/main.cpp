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
#include <QDebug>
#include<QString>

#define ARAIGNEE_PLY "../donneeTestDIAS/araignee.ply"
#define POINT3D "C:/code04Mai2015/constructionOctree4Mai/Point3D_v3.txt"
#define SALAMANDRE_TXT "../donneeTestDIAS/SalamandreCloud.txt"


/* Type de construction attendue */
//#define CONSTRUIRE_KD
//#define CONSTRUIRE_OCTREE
//#define CONSTRUIRE_RTREE
#define SIMPLE_OCTREE


#ifndef _WIN32
#include <sys/time.h>

double stopwatch2() // idem as Stopwatch.h
{
    struct timeval time;
    gettimeofday(&time, 0 );
    return 1.0 * time.tv_sec + time.tv_usec / (double)1e6;
}

#else

#include <windows.h>
double stopwatch2()
{
    unsigned long long ticks;
    unsigned long long ticks_per_sec;
    QueryPerformanceFrequency( (LARGE_INTEGER *)&ticks_per_sec);
    QueryPerformanceCounter((LARGE_INTEGER *)&ticks);
    return ((float)ticks) / (float)ticks_per_sec;
}

#endif



using namespace std;
int main(int argc, char** argv)
{
    double startApplication, endComputing, startResize, getNP, stopRead,
            startRead, startOpenFile, startNaiveQuery, stopNaiveQuery,
            vec3start, vec3stop;
    startApplication = stopwatch2();


    // Read command lines arguments.
    QApplication application(argc,argv);


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

    startOpenFile = stopwatch2();
    Fichier donnees(SALAMANDRE_TXT);
    startRead = stopwatch2();
    Point ** pointsDonnees = donnees.getPoints();
    stopRead = stopwatch2();
    int nbPoints = donnees.getNbPoints();
    getNP = stopwatch2();


    vec3start = stopwatch2();
    /* Code récupéré sur https://github.com/brandonpelfrey/SimpleOctree/ */
    // Create a new Octree centered at the origin
    // with physical dimension 2x2x2
    Vec3 qmin, qmax;
    std::vector<Vec3> points;
    Point * p = NULL;
    {
        // Calcul du voxel englobant et conversion
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
    }
    vec3stop = stopwatch2();

#ifdef SIMPLE_OCTREE
    Vec3 origin((qmax.x + qmin.x) /2, (qmax.y + qmin.y)/2, (qmax.z + qmin.z)/2);
    Vec3 half((qmax.x + qmin.x) /2, (qmax.y + qmin.y)/2, (qmax.z + qmin.z)/2);
    brandonpelfrey::Octree *octree = new brandonpelfrey::Octree(origin, half);
    OctreePoint *octreePoints = NULL;
    init(octree, octreePoints, points, qmin, qmax);
    testOctree(octree, qmin, qmax);
#endif

    viewer.setWindowTitle("simpleViewer");
    viewer.setFPSIsDisplayed(true);

    // Make the viewer window visible on screen.
    viewer.show();



    qmin.x = -1; qmin.y = 5; qmin.z = -11;
    qmax.x = 0; qmax.y = 6; qmax.z = -10;
    startNaiveQuery = stopwatch2();
    std::vector<int> champDeVision;
    testNaive(points, qmin, qmax, champDeVision);
    stopNaiveQuery = stopwatch2();

    viewer.qmin = qmin;
    viewer.qmax = qmax;
    viewer.m_tailleAfficher = champDeVision.size();
    Point ** affichage = new Point*[viewer.m_tailleAfficher];

    startResize = stopwatch2();
    //for(int i = 0 ; i < viewer.m_tailleAfficher ; i++) {
    //    pointsDonnees[i]->setX(pointsDonnees[i]->getX() /10);
    //    pointsDonnees[i]->setY(pointsDonnees[i]->getY() /10);
    //    pointsDonnees[i]->setZ(pointsDonnees[i]->getZ() /10);
    //}
    for(int i = 0 ; i < viewer.m_tailleAfficher ; i++) {
        affichage[i] = pointsDonnees[champDeVision[i]];
    }
    endComputing = stopwatch2();

    viewer.m_afficher = pointsDonnees;


    qDebug() << "Loading data";
    qDebug() << "    Reading file in " << stopRead - startRead;
    qDebug() << "    Total access file time : " << getNP - startOpenFile;
    qDebug() << "    Converted " << nbPoints << " points in " << vec3stop - vec3start;
    qDebug() << "Query 1";
    qDebug() << "    Result in " << stopNaiveQuery - startNaiveQuery;
    qDebug() << "    Converted " << viewer.m_tailleAfficher << "points in " << endComputing - startResize;

    // Run main loop.
    int runCode = application.exec();


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

    for(int i = 0 ; i < viewer.m_tailleAfficher ; i++) {
        delete pointsDonnees[i];
    }
    delete pointsDonnees;
    return runCode;
}

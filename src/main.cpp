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
//#define CONSTRUIRE_KD
//#define CONSTRUIRE_OCTREE
//#define CONSTRUIRE_RTREE
#define SIMPLE_OCTREE

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>

#include "../SimpleOctree/Octree.h"
#include "../SimpleOctree/Stopwatch.h"

using namespace brandonpelfrey;

// Used for testing
std::vector<Vec3> points;
brandonpelfrey::Octree *octree;
OctreePoint *octreePoints;
Vec3 qmin, qmax;

float rand11() // Random number between [-1,1]
{ return -1.f + (2.f*rand()) * (1.f / RAND_MAX); }

Vec3 randVec3() // Random vector with components in the range [-1,1]
{ return Vec3(rand11(), rand11(), rand11()); }

// Determine if 'point' is within the bounding box [bmin, bmax]
bool naivePointInBox(const Vec3& point, const Vec3& bmin, const Vec3& bmax) {
    return
        point.x >= bmin.x &&
        point.y >= bmin.y &&
        point.z >= bmin.z &&
        point.x <= bmax.x &&
        point.y <= bmax.y &&
        point.z <= bmax.z;
}

void init() {
    // Create a new Octree centered at the origin
    // with physical dimension 2x2x2
    octree = new brandonpelfrey::Octree(Vec3(0,0,0), Vec3(1,1,1));

    // Create a bunch of random points
    const int nPoints = 1 * 1000 * 1000;
    for(int i=0; i<nPoints; ++i) {
        points.push_back(randVec3());
    }
    printf("Created %ld points\n", points.size()); fflush(stdout);

    // Insert the points into the octree
    octreePoints = new OctreePoint[nPoints];
    for(int i=0; i<nPoints; ++i) {
        octreePoints[i].setPosition(points[i]);
        octree->insert(octreePoints + i);
    }
    printf("Inserted points to octree\n"); fflush(stdout);

    // Create a very small query box. The smaller this box is
    // the less work the octree will need to do. This may seem
    // like it is exagerating the benefits, but often, we only
    // need to know very nearby objects.
    qmin = Vec3(-.05,-.05,-.05);
    qmax = Vec3(.05,.05,.05);

    // Remember: In the case where the query is relatively close
    // to the size of the whole octree space, the octree will
    // actually be a good bit slower than brute forcing every point!
}

// Query using brute-force
void testNaive() {
    double start = stopwatch();

    std::vector<int> results;
    for(int i=0; i<points.size(); ++i) {
        if(naivePointInBox(points[i], qmin, qmax)) {
            results.push_back(i);
        }
    }

    double T = stopwatch() - start;
    printf("testNaive found %ld points in %.5f sec.\n", results.size(), T);
}

// Query using Octree
void testOctree() {
    double start = stopwatch();

    std::vector<OctreePoint*> results;
    octree->getPointsInsideBox(qmin, qmax, results);

    double T = stopwatch() - start;
    printf("testOctree found %ld points in %.5f sec.\n", results.size(), T);
}

int main(int argc, char *argv[])
{

#ifdef SIMPLE_OCTREE
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

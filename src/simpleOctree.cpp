/* https://github.com/brandonpelfrey/SimpleOctree/ */


#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>

#include "../include/simpleOctree.h"
#include "../SimpleOctree/Octree.h"
#include "../SimpleOctree/Stopwatch.h"

using namespace brandonpelfrey;

// Used for testing

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

void init(Octree *octree, OctreePoint *octreePoints, std::vector<Vec3> &points, Vec3 &qmin, Vec3 &qmax) {
    // Create a bunch of random points
    //const int nPoints = 1 * 1000 * 1000;
    //for(int i=0; i<nPoints; ++i) {
    //    points.push_back(randVec3());
    //}
    //printf("Created %ld points\n", points.size()); fflush(stdout);

    // Insert the points into the octree
    const int nPoints = points.size();
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
void testNaive(std::vector<Vec3> points, Vec3 qmin, Vec3 qmax) {
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
void testOctree(Octree *octree, Vec3 qmin, Vec3 qmax) {
    double start = stopwatch();

    std::vector<OctreePoint*> results;
    octree->getPointsInsideBox(qmin, qmax, results);

    double T = stopwatch() - start;
    printf("testOctree found %ld points in %.5f sec.\n", results.size(), T);
}

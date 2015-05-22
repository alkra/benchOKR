#ifndef SIMPLEOCTREE_H
#define SIMPLEOCTREE_H

#include "../SimpleOctree/Octree.h"

bool naivePointInBox(const Vec3& point, const Vec3& bmin, const Vec3& bmax);

void init(brandonpelfrey::Octree* octree, OctreePoint* octreePoints, Vec3 **points, int nPoints, Vec3 &qmin, Vec3& qmax);
void testNaive(std::vector<Vec3> points, Vec3 qmin, Vec3 qmax, std::vector<int> &results);
void testOctree(brandonpelfrey::Octree* octree, Vec3 qmin, Vec3 qmax, std::vector<OctreePoint *> &results);

#endif // SIMPLEOCTREE_H

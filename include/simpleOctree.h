#ifndef SIMPLEOCTREE_H
#define SIMPLEOCTREE_H

#include "../SimpleOctree/Octree.h"

brandonpelfrey::Octree* init();
void testNaive(std::vector<Vec3> points, Vec3 qmin, Vec3 qmax);
void testOctree(brandonpelfrey::Octree* octree, Vec3 qmin, Vec3 qmax);

#endif // SIMPLEOCTREE_H

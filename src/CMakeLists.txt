INCLUDE_DIRECTORIES(../include)

set(SRCS
    Arbre.cpp
    Fichier.cpp
    KdTree.cpp
    main.cpp
    Noeud.cpp
    NoeudKd.cpp
    NoeudOctree.cpp
    NoeudR.cpp
    Octree.cpp
    Point3D.cpp
    Point.cpp
    RTree.cpp
)

add_executable(benchOKR ${SRCS} ${INCLUDES})

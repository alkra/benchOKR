QT  += core
QT += widgets
QT += xml
QT += opengl
TARGET = benchOKR
SOURCES += ../src/Arbre.cpp \
    ../src/main.cpp \
    ../src/Fichier.cpp \
    ../src/KdTree.cpp \
    ../src/Noeud.cpp \
    ../src/NoeudKd.cpp \
    ../src/NoeudOctree.cpp \
    ../src/NoeudR.cpp \
    ../src/Octree.cpp \
    ../src/Point.cpp \
    ../src/Point3D.cpp \
    ../src/RTree.cpp \
    ../src/Voxel.cpp \
    ../src/simpleOctree.cpp \
    ../src/simpleViewer.cpp \
    ../src/mainwindow.cpp
HEADERS += ../include/Arbre.h \
    ../include/Fichier.h \
    ../include/KdTree.h \
    ../include/Noeud.h \
    ../include/NoeudKd.h \
    ../include/NoeudOctree.h \
    ../include/NoeudR.h \
    ../include/Octree.h \
    ../include/Point.h \
    ../include/Point3D.h \
    ../include/RTree.h \
    ../include/Voxel.h \
    ../SimpleOctree/Stopwatch.h \
    ../SimpleOctree/Vec3.h \
    ../SimpleOctree/OctreePoint.h \
    ../SimpleOctree/Octree.h \
    ../include/simpleOctree.h \
    ../include/simpleViewer.h \
    ../include/mainwindow.h

INCLUDEPATH *= /usr/include
LIBS *= -L/usr/lib -lQGLViewer

QMAKE_CXXFLAGS += -std=c++11

FORMS += \
    ../ressources/mainwindow.ui

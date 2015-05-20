QT  += core
QT  += core gui
QT  += xml
QT  += opengl
QT  -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app



HEADERS+

INCLUDEPATH *=../lib/libQGLViewer-2.6.1/libQGLViewer-2.6.1
LIBS *= -L../lib/libQGLViewer-2.6.1/libQGLViewer-2.6.1 -lQGLViewer2


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
    ../src/simpleViewer.cpp
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
    ../include/simpleViewer.h

QMAKE_CXXFLAGS += -std=c++11

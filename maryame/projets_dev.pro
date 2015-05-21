#-------------------------------------------------
#
# Project created by QtCreator 2015-03-12T17:04:58
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = benchOKR
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += ../src/main.cpp \
    ../src/Arbre.cpp \
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
    ../src/Voxel.cpp

HEADERS += \
    point.h \
    readstockpoint.h \
    ../include/Arbre.h \
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
    ../include/Voxel.h

QMAKE_CXXFLAGS += -std=c++11

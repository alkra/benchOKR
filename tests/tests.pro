#-------------------------------------------------
#
# Project created by QtCreator 2015-04-08T13:55:37
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    testsVoxel.cpp \
    testsFichier.cpp \
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
    testsVoxel.h \
    testsFichier.h

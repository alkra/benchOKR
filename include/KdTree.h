#ifndef KDTREE_H
#define KDTREE_H

/* �ENSG 2015
 * �cole nationale des sciences g�ographiques
 * 6-8 avenue Blaise Pascal
 * Cit� Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALL�E CEDEX 2
 * FRANCE */

/* Ce fichier d�finit la classe KdTree.
 * Cette classe h�rite de Arbre et repr�sente le stockage par la m�thode du
 * Kd-tree. */

#include "Arbre.h"
#include "Point3D.h"
#include "Voxel.h"
#include"KdTree.h"
#include"NoeudKd.h"

#include <string>

using namespace std;

class KdTree : public Arbre  // Cr�ation d'une classe KdTree qui h�rite de la classe Arbre
{
    public:
        KdTree();
        ~KdTree();

        //void construire1(string path,int niveau,string Path);

        void construire();
        NoeudKd* construire1();
        Point* requete(const Point &centre, double distance) const; // voisinage
        Point* requete(const Voxel &conteneur) const; // dans un voxel
        double** lirefichiertxt(std::string Path,int lignes);//mettre les majusculle entre deux mots
        double** lirefichierply(std::string Path,int lignes);//impl�menter la lecture du fichier binaire
        double** triePoint(int n,int d,int j,double** v1);
        int* CalculIndiceMedian(string Path,int depth);
        int* CalculIndicePlanMedian(string Path,int depth);
        //void construire1(double** v1,int median,int ligne);
        Voxel calculvoxel(double** v1,int debut,int fin);
        string* CreerNoeud(string P);
        int calculPoints(string Path);


    protected:

        Point3D point;
        Point3D* tabpointmedian;
        Voxel* tabvoxel;
        NoeudKd* P;


    private:
};

#endif // KDTREE_H

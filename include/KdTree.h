#ifndef KDTREE_H
#define KDTREE_H

/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier définit la classe KdTree.
 * Cette classe hérite de Arbre et représente le stockage par la méthode du
 * Kd-tree. */

#include "Arbre.h"
#include "Point3D.h"
#include "Voxel.h"
#include "KdTree.h"
#include "NoeudKd.h"

#include <string>

using namespace std;

class KdTree : public Arbre<NoeudKd>  // Création d'une classe KdTree qui hérite de la classe Arbre
{
    public:
        KdTree();
        ~KdTree();

        void construire(const QString& racine, const QString& cheminDonnes);

        NoeudKd* construire1(const QString& rootPath, const QString &cheminDonnees,const int& niveau);
        //NoeudKd* construire1();
        QVector<Point> requete(const Point &centre, double distance) const; // voisinage
        QVector<Point> requete(const Voxel &conteneur) const; // dans un voxel
        double** lirefichiertxt(std::string Path,int lignes);//mettre les majusculle entre deux mots
        double** lirefichierply(std::string Path,int lignes);//implèmenter la lecture du fichier binaire
        double** triePoint(int n,int d,int j,double** v1);
        int* CalculIndiceMedian(string Path,int depth);
        int* CalculIndicePlanMedian(string Path,int depth);
        //void construire1(double** v1,int median,int ligne);
        Voxel calculvoxel(double** v1,int debut,int fin);
        string* CreerNoeud(const string &path);
        int calculPoints(string Path);
        Voxel* calculvoxelmedian(Voxel v,int i,double median);


    protected:

        Point3D point;
        Point3D* tabpointmedian;
        Voxel* tabvoxel;

public:
        NoeudKd* root;


    private:
};

#endif // KDTREE_H

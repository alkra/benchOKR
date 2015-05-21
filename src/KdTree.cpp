/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation de la classe KdTree. */

#include "../include/KdTree.h"
#include "../include/Point3D.h"
#include "../include/Voxel.h"
#include "../include/NoeudKd.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
//#include <windows.h>

#include <sstream>



using namespace std;


KdTree::KdTree()
{
    //ctor
}

KdTree::~KdTree()
{
    if(racine) {
        delete racine;
    }
}

void KdTree::construire(const QString& rootPath, const QString& cheminDonnees) {

}

NoeudKd* KdTree::construire1(const QString& rootPath, const QString& cheminDonnees,const int& niveau)  {
    string path = cheminDonnees.toStdString();
    int lignes = calculPoints(path); // Fichier donnees(path); lignes = donnees.getNbPoints();
    double** v1; // ?
    int NbreIndiceMedian=0;
    int NbreVoxel;
    int k1=0; // ?




    while (niveau>=k1)
    {
        NbreIndiceMedian += pow(2,k1)+1;
        k1++; // du coup tu peux faire une boucle for
    }
    k1=0;
    while (niveau>=k1) // toujours faux
    {
        NbreVoxel += pow(2,k1);
        k1++;
    }

    int nbremedian = pow(2,niveau)-1;
    int *indiceplanmedian=new int[nbremedian];
    tabpointmedian=new Point3D[nbremedian];


    int *median=new int[NbreIndiceMedian];
    cout<<NbreIndiceMedian<<endl;
    cout<<nbremedian<<endl;

    median= CalculIndiceMedian(path,niveau);
    indiceplanmedian=CalculIndicePlanMedian(path,niveau);

    v1=lirefichierply(path,lignes);


    tabvoxel=new Voxel[NbreVoxel];
    tabvoxel[0]=calculvoxel(v1,0,lignes);
    cout<<"nbre de voxel"<<endl;
    int n=0;
    int i=1;
    int i2=1;
    int i3=0;
    while ( i<NbreIndiceMedian ){
        if ( median[i]!=0 )
        {
            cout<<median[i]<<" "<<endl;
            v1=triePoint(median[i],median[i-1],n,v1);// trie par colonne j jusqu'a l'element d
            //tabvoxel[i3]=calculvoxel(v1,median[i-1],median[i]);
            if(i2<=nbremedian)
            {
                //cout<<indiceplanmedian[i2-1]<<"::::lah isahal"<<endl;
                // point.setX(0);
                point.setX(v1[indiceplanmedian[i2-1]][0]);
                point.setY(v1[indiceplanmedian[i2-1]][1]);
                point.setZ(v1[indiceplanmedian[i2-1]][2]);
                tabpointmedian[i2]=point;
                cout<<tabpointmedian[i2].getX()<<" yalah"<<tabpointmedian[i2].getY()<<endl;

                i2++;
            }
            i3++;
            i++;
        }
        else
        {
            i++;
            if (n<3)
            {
                n++;
            }
            else
            {
                n=0;
            }
        }

    }


    //Creation de l'Arborescente Binaire
    string* T;
    int NiveauArray=0;

    for(int i5=1;i5<niveau+1;i5++){
    NiveauArray=NiveauArray+pow(2,i5);
    }
    T=CreerNoeud(rootPath.toStdString());
    string *array=new string[2];
    string *array1=new string[NiveauArray];//ON DEFINIT LE NIVEAU DE L'ARBORESCENCE .
    array1[0]=T[0];
    array1[1]=T[1];

  //cout<<NiveauArray<<"niveau array::::"<<T[1]<<endl;
    string Path;
   int j=2;
   if ((NiveauArray-pow(2,niveau))!=0){
   for (int i=0;i<(NiveauArray-pow(2,niveau));i++) //ON DEFINIT NIVEAU-1
{

     Path=array1[i];
     array=CreerNoeud(Path);
     array1[j]=array[0];
     array1[j+1]=array[1];
     j+=2;


}
    }
   int c1=j;
//creation des sous fichiers,
   int puis=NbreIndiceMedian-(pow(2,niveau)+1);
   //cout<<"PUISSANCE"<<puis<<endl;
   int i1=NiveauArray-pow(2,niveau);
   for (int i=puis;i<NbreIndiceMedian-1;i++)
    {

    string P=array1[i1];
    //cout<<"array"<<P<<endl;
    P +="/data.txt";

    const char* c= P.c_str(); //Convertion du Qstring to char*
    //creation de fichier de points
    ofstream f(c);
    if (!f.is_open())
        cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
    else
    {



            //cout<<median[i]<<"kkkkkk"<<median[i+1]<<endl;
            for (int k=median[i]; k <median[i+1]; k++){

             f << v1[k][0] <<" "<<v1[k][1]<<" "<<v1[k][2]<<"\n";}




        f.close();
    }
        i1++;
        P="/0";}
    //createtree(v1);

   //calculvoxel median
   //Voxel v1;
   Voxel* Tab_median;
   Tab_median=new Voxel[2];
   int NiveauArray1=0;

   double lamedian=tabpointmedian[1].getX();
   cout<<"la median"<<lamedian<<endl;
   Tab_median=calculvoxelmedian(tabvoxel[0],0,lamedian);
   double y1=Tab_median[0].getDebut().getX();
   cout<<"tab median"<<Tab_median[0].getDebut().getX()<<" "<<Tab_median[0].getDebut().getY()<<endl;


   for(int i5=1;i5<niveau+1;i5++){
   NiveauArray1=NiveauArray1+pow(2,i5);
   }

   Voxel *voxel_array1=new Voxel[NiveauArray1];//ON DEFINIT LE NIVEAU DE L'ARBORESCENCE .
   voxel_array1[0]=Tab_median[0];
   voxel_array1[1]=Tab_median[1];

   //cout<<NiveauArray1<<"niveau array1"<<T[1]<<endl;
   Voxel v_pivot;
  int j3=2;
  int k=1;
  int d=NiveauArray1-pow(2,niveau);
  int i12=0;
  if ((NiveauArray1-pow(2,niveau))!=0){
  while (i12<(NiveauArray1-pow(2,niveau))) //ON DEFINIT NIVEAU-1
{
    if(k<3)
    {
    v_pivot=voxel_array1[i12];
    cout<<voxel_array1[i12].getDebut().getX()<<"voxel"<<endl;
    if (k==0){
    Tab_median=calculvoxelmedian(v_pivot,k,tabpointmedian[i12+1].getX());}
    if (k==1){
    Tab_median=calculvoxelmedian(v_pivot,k,tabpointmedian[i12+1].getY());}
    if (k==2){
    Tab_median=calculvoxelmedian(v_pivot,k,tabpointmedian[i12+1].getZ());}
    voxel_array1[j3]=Tab_median[0];
    voxel_array1[j3+1]=Tab_median[1];
    j3+=2;
    k++;
    i12++;
    }
    else
    {
        k=0;
    }

}
   }


    int c=j3;

    root=new NoeudKd[NbreVoxel+1];
    cout<<NbreVoxel<<endl;
    root[0].setDossier(QString(rootPath));
    root[0].setVoxel(tabvoxel[0]);
    for (int i=1;i<=NiveauArray;i++)
    {
        root[i].setDossier(QString(array1[i-1].c_str()));
        root[i].setVoxel(voxel_array1[i-1]);
    }

    //affichage du decoupage kd : voxels et chemins
    for (int i=0;i<NiveauArray+1;i++)
    {

        cout<<root[i].getDossier().absolutePath().toLocal8Bit().data()<<endl;

        cout<<"element1 du tableau"<<root[i].getVoxel().getDebut().getX()<<endl;
        cout<<"element2 du tableau"<<root[i].getVoxel().getDebut().getY()<<endl;
        cout<<"element3 du tableau"<<root[i].getVoxel().getDebut().getZ()<<endl;
        cout<<"element2 du tableau"<<root[i].getVoxel().getFin().getX()<<endl;
        cout<<"element3 du tableau"<<root[i].getVoxel().getFin().getY()<<endl;
        cout<<"element3 du tableau"<<root[i].getVoxel().getFin().getZ()<<endl;
    }




    return root;

}



QVector<Point> KdTree::requete(const Point &centre, double distance) const
{
    // requête sur un voisinage
}

QVector<Point> KdTree::requete(const Voxel &conteneur) const {
    // requête dans un voxel
}


double** KdTree::lirefichiertxt(string Path,int lignes){

    double** v1 = 0;
    v1 = new double*[lignes];

    for (int i = 0; i < lignes; i++)
    {
        v1[i] = new double[lignes];

        for (int k = 0; k < 3; k++)
        {
            // fill in some initial values
            // (filling in zeros would be more logic, but this is just for the example)
            v1[i][k] = i + 3 * k;
        }
    }

    int i;


    // lecture d'un fichier txt
    ifstream f (Path.c_str());//"E:/Test/toto.txt"

    if (!f.is_open())
        cout << "Impossible d'ouvrir le fichier en lecture !" << endl;
    else
    {

        for (i = 0; i < lignes; i++)
            for (int k = 0; k < 3; k++)
                f >> v1[i][k];
        // Affectation des valeurs du fichier txt à la matrice v1
    }
    f.close();

    // Lecture de la matrice v1
    for (i = 0; i < lignes; i++){
        for (int k = 0; k < 3; k++){
            cout <<  v1[i][k] <<"\t";

        }
        cout << "\n";
    }

    return v1;


}

double** KdTree::lirefichierply(string Path,int lignes){

    char* pEnd;
    char* pEnd1;

    double** v1 = 0;
    v1 = new double*[lignes];

    for (int i = 0; i < lignes; i++)
    {
        v1[i] = new double[lignes];

        for (int k = 0; k < 3; k++)
        {
            // fill in some initial values
            // (filling in zeros would be more logic, but this is just for the example)
            v1[i][k] = i + 3 * k;
        }
    }





    ifstream fichier (Path.c_str(),ios::in);


    if(fichier)  // si l'ouverture a réussi
    {
        string info;
        getline(fichier, info);
        if (info=="ply")
            cout << "le fichier ouvert est un fichier .ply" << endl;

        int i=0;
        QString ligne;
        QStringList liste;
        while (std::getline(fichier, info) && i<lignes)
        {
            //GotoLine(file, 8);

            {
                if ( atoi(info.c_str()))  //check that the input is number
                    // if (i>8 && i<963)
                {
                    ligne.fromStdString(info);
                    liste = ligne.split(' ');
                    if(liste.size() >= 3) {
                        v1[i][0] = liste[0].toDouble();
                        v1[i][1]= liste[1].toDouble();
                        v1[i][2] = liste[2].toDouble();
                    }

                    // cout <<v1[i][0]<<" "<<v1[i][1]<<" "<<v1[i][2]<< endl;
                    i++;


                }



            }

        }
        /* if( result==NULL){
             cout<<"la ligne %d n'existe pas dans le fichier"<<line<<endl;
         }*/

        fichier.close();
        // on ferme le fichier


    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    return v1;



}


double** KdTree::triePoint(int n,int d,int j,double** v1)
//n: nbre des element du tableau j:trie en colonne j(trie par colonne j)
{
    double t1[3];

    for(int i=d;i<n;i++)
        for(int k=i;k<n;k++) {

            {

                if(v1[i][j]>v1[k][j])
                {

                    t1[0]=v1[i][0];
                    t1[1]=v1[i][1];
                    t1[2]=v1[i][2];
                    v1[i][0]=v1[k][0];
                    v1[i][1]=v1[k][1];
                    v1[i][2]=v1[k][2];
                    v1[k][0]=t1[0];
                    v1[k][1]=t1[1];
                    v1[k][2]=t1[2];

                }

            }
        }

    //Affichage de la matrice triée
    /*for(int i=d;i<n;i++) {
           printf("\n");
           for(int j=d;j<3;j++) {
               printf("\t",v1[i][j]);
           }
       }*/

    return v1;
}

//fonction qui renvoie les indices des medianes
int *KdTree::CalculIndiceMedian(string Path,int depth) //i est le nombre de lignes + j est la collones triée
{
    int NbreIndiceMedian=0;
    int i=0;
    int j=0;
    int k1=0;
    while (depth+1>k1)
    {
        NbreIndiceMedian=NbreIndiceMedian +(pow(2,k1)+1);
        k1++;
    }

    cout<<NbreIndiceMedian<<endl;
    int *T=new int[NbreIndiceMedian];
    int n1=calculPoints(Path);


    while ((i<NbreIndiceMedian) && j<(depth+1))
    {
        int a=0;
        int d=pow(2,j);
        while (a<=d){
            int c=floor((n1*a)/d);
            //cout << "Mediane == " << v1[c][j] << endl;
            T[i]=c;
            a++;
            i++;
        }
        j++;

    }
    for(int i=0;i<NbreIndiceMedian;i++){

        cout<<T[i]<<endl;}

    return T;

}


int *KdTree::CalculIndicePlanMedian(string Path,int depth) //i est le nombre de lignes + j est la collones triée
{
    int nbremedian=(pow(2,depth)-1);
    int *T=new int[nbremedian];
    int n1=calculPoints(Path);

    int i=0;
    int j=1;

    while (i<nbremedian && j<(depth+1))
    {
        int a=1;
        int d=pow(2,j);
        while (a<d)
        {
            int c=floor((n1*a)/d);
            //cout << "Mediane == " << v1[c][j] << endl;
            T[i]=c;
            a=a+2;
            i++;
        }
        j++;

    }

    return T;

}







/*void KdTree::construire(double** v1,int median,int lignes){

   // QString Path="E:/Test/k";
   // for(int i=0;i<10;i++)
   // {

    for (int j1=1;j1<3;j1++)
    {

        QString Path;
        Path = QString("E:/Test/k/k1/k%1").arg(j1);

        QDir mdir(Path);


        if(!mdir.exists(Path))
        {
            mdir.mkpath(Path);
            qDebug()<<"Created";
        }
        else
        {
            qDebug()<<"Already exists";
        }



    // }

        Path +="/toto1.txt";
        const char* c= Path.toStdString().c_str(); //Convertion du Qstring to char*
        //creation de fichier de points
        ofstream f(c);
        if (!f.is_open())
            cout << " Impossible d'ouvrir le fichier en écriture !" << endl;
        else
        {
            if (j1==1)
            {for (int i = 0; i <median; i++)

                    f << v1[i][0] <<" "<<v1[i][1]<<" "<<v1[i][2]<<"\n";
            }
            else
            {
                for (int i = 8; i <lignes; i++)

                    f << v1[i][0] <<" "<<v1[i][1]<<" "<<v1[i][2]<<"\n";
            }

            f.close();

        }
          Path="/0";

   }
}*/



string* KdTree::CreerNoeud(const string &path){
    // Création des dossiers
    QDir dossierParent;
    dossierParent.setPath(QString(path.c_str()));
    QString Path1 = dossierParent.absoluteFilePath("Z1");
    QString Path2 = dossierParent.absoluteFilePath("Z2");

    if(!dossierParent.exists(Path1))
    {
        dossierParent.mkpath(Path1);
        qDebug() << "Created folder " << Path1;
    }
    if(!dossierParent.exists(Path2))
    {
        dossierParent.mkpath(Path2);
        qDebug() << "Created folder" << Path2;
    }
    else
    {
        qDebug()<<"Already exists";
    }


    string *T= new string[2]; // à détruire
    T[0]=Path1.toStdString();
    T[1]=Path2.toStdString();
    return T;
}



int KdTree ::calculPoints(string Path)
{

    ifstream fichier (Path.c_str(),ios::in);


    int i=0;

    if(fichier)  // si l'ouverture a réussi
    {
        string info;
        getline(fichier, info);
        if (info=="ply")
            cout << "le fichier ouvert est un fichier .ply" << endl;


        while (std::getline(fichier, info))
        {
            //GotoLine(file, 8);
            if ( atoi(info.c_str()))  //check that the input is number
                // if (i>8 && i<963)
            {
                i++;
            }
        }


        fichier.close();  // on ferme le fichier
    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    return i;

}


Voxel KdTree ::calculvoxel(double** v,int debut,int fin)
{
    Point3D xmax,xmin;
    Voxel voxel;
    double max1=v[0][0];
    double max2=v[0][1];
    double max3=v[0][2];
    double min1=v[0][0];
    double min2=v[0][1];
    double min3=v[0][2];

    for (int i=debut;i<fin;i++)
    {

        if (v[i][0]>max1)
        {
            max1=v[i][0];
        }
        if (v[i][1]>max2)
        {
            max2=v[i][1];
        }

        if (v[i][2]>max3)
        {
            max3=v[i][2];
        }


        if (v[i][0]<min1)
        {
            min1=v[i][0];
        }
        if (v[i][1]<min2)
        {
            min2=v[i][1];
        }

        if (v[i][2]<min3)
        {
            min3=v[i][2];
        }

    }

    xmax.setX(max1);
    xmax.setY(max2);
    xmax.setZ(max3);
    xmin.setX(min1);
    xmin.setY(min2);
    xmin.setZ(min3);

    voxel.setDebut(xmin);
    voxel.setFin(xmax);

    return voxel;
}

Voxel* KdTree ::calculvoxelmedian(Voxel vcourant,int i,double median)//i indice le plan de separation
{

    Voxel* voxel;
    voxel=new Voxel[2];
    Voxel v1,v2;
    Point3D p1 = v1.getDebut();
    Point3D p2 = v1.getFin();
    Point3D p3 = v2.getDebut();
    Point3D p4 = v2.getFin();


    double x1=0,y1=0,z1=0,x2=0,y2=0,z2=0,x3=0,y3=0,z3=0,x4=0,y4=0,z4=0;
    if(i==0)
       {
        cout<<"x2 ::::"<<vcourant.getDebut().getX()<<median<<endl;

    x1=vcourant.getDebut().getX();
    y1=vcourant.getDebut().getY();
    z1=vcourant.getDebut().getZ();
    x2=median;
    y2=vcourant.getFin().getY();
    z2=vcourant.getFin().getZ();

     x3= median;
     y3=vcourant.getDebut().getY();
     z3=vcourant.getDebut().getZ();
     x4=vcourant.getFin().getX();
     y4=vcourant.getFin().getY();
     z4=vcourant.getFin().getZ();

    p1.setX(x1);
    p1.setY(y1);
    p1.setZ(z1);

    p2.setX(x2);
    p2.setY(y2);
    p2.setZ(z2);

    p3.setX(x3);
    p3.setY(y3);
    p3.setZ(z3);

    p4.setX(x4);
    p4.setY(y4);
    p4.setZ(z4);

    v1.setDebut(p1);
    v1.setFin(p2);
    v2.setDebut(p3);
    v2.setFin(p4);

  cout<<"test:::"<<x1<<"="<<v1.getDebut().getX()<<endl;

    }
 else{
    if(i==1)
       {
    x1= vcourant.getDebut().getX();
    y1=vcourant.getDebut().getY();
    z1=vcourant.getDebut().getZ();
    x2=vcourant.getFin().getX();
    y2=median;
    z2=vcourant.getFin().getZ();

    x3=vcourant.getDebut().getX();
    y3=median;
    z3=vcourant.getDebut().getZ();
    x4=vcourant.getFin().getX();
    y4=vcourant.getFin().getY();
    z4=vcourant.getFin().getZ();

    p1.setX(x1);
    p1.setY(y1);
    p1.setZ(z1);

    p2.setX(x2);
    p2.setY(y2);
    p2.setZ(z2);

    p3.setX(x3);
    p3.setY(y3);
    p3.setZ(z3);

    p4.setX(x4);
    p4.setY(y4);
    p4.setZ(z4);

    v1.setDebut(p1);
    v1.setFin(p2);
    v2.setDebut(p3);
    v2.setFin(p4);


    }
   else{
    if(i==2)
       {
    x1=vcourant.getDebut().getX();
    y1=vcourant.getDebut().getY();
    z1=vcourant.getDebut().getZ();
    x2=vcourant.getFin().getX();
    y2=vcourant.getFin().getY();
    z2=median;

    x3=vcourant.getDebut().getX();
    y3=vcourant.getDebut().getY();
    z3=median;
    x4=vcourant.getFin().getX();
    y4=vcourant.getFin().getY();
    z4=vcourant.getFin().getZ();

    p1.setX(x1);
    p1.setY(y1);
    p1.setZ(z1);

    p2.setX(x2);
    p2.setY(y2);
    p2.setZ(z2);

    p3.setX(x3);
    p3.setY(y3);
    p3.setZ(z3);

    p4.setX(x4);
    p4.setY(y4);
    p4.setZ(z4);

    v1.setDebut(p1);
    v1.setFin(p2);
    v2.setDebut(p3);
    v2.setFin(p4);
    }

  }
    }
    voxel[0]=v1;
    voxel[1]=v2;
    return voxel;
}

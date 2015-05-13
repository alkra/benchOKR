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
#include <windows.h>

#include <sstream>



using namespace std;


KdTree::KdTree()
{
    //ctor
}

KdTree::~KdTree()
{
    //dtor
}

/*void KdTree::construire1(string path,int niveau,string Path)
    {
    // Code spécifique au kd-tree

    int lignes = calculPoints(path);
    double** v1;
    int NbreIndiceMedian=0;
    int NbreVoxel;
    int k1=0;




    while (niveau>=k1)
    {
    NbreIndiceMedian=NbreIndiceMedian+(pow(2,k1)+1);
    k1++;
    }

    while (niveau>=k1)
    {
    NbreVoxel=NbreVoxel+(pow(2,k1));
    k1++;
    }

    int nbremedian=(pow(2,niveau)-1);
    int *indiceplanmedian=new int[nbremedian];
    tabpointmedian=new Point3D[nbremedian];


    int *median=new int[NbreIndiceMedian];
    cout<<NbreIndiceMedian<<endl;
    cout<<nbremedian<<endl;

    median= CalculIndiceMedian(path,niveau);
    indiceplanmedian=CalculIndicePlanMedian(path,niveau);

    v1=lirefichierply(path,lignes);


    tabvoxel=new Voxel[NbreVoxel];
    cout<<"nbre de voxel"<<endl;
    int n=0;
    int i=1;
    int i2=1;
    int i3=0;
    while ( i<NbreIndiceMedian ){
    if ( median[i]!=0 )
    {   cout<<median[i]<<" "<<endl;
        v1=triePoint(median[i],median[i-1],n,v1);// trie par colonne j jusqu'a l'element d
        tabvoxel[i3]=calculvoxel(v1,median[i-1],median[i]);
        if(i2<=nbremedian)
        {
        //cout<<indiceplanmedian[i2-1]<<"::::lah isahal"<<endl;
       // point.setX(0);
        point.setX(v1[indiceplanmedian[i2-1]][0]);
        point.setY(v1[indiceplanmedian[i2-1]][1]);
        point.setZ(v1[indiceplanmedian[i2-1]][2]);
        tabpointmedian[i2]=point;

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

    cout<<"hamdolah"<<endl;
    //Creation de l'Arborescente Binaire

    string* T;

    T=CreerNoeud(Path);
    int j1=1;
    int elm=0;
    while(j1<=niveau)
    {
        elm=elm+(pow(2,niveau));
        j1++;
    }
    string *array=new string[2];
    string *array1=new string[elm];//ON DEFINIT LE NIVEAU DE L'ARBORESCENCE .
    array1[0]=T[0];
    array1[1]=T[1];

  // cout<<T[0]<<""<<T[1]<<endl;
   int j=2;
   int elm_1=0;
   int j2=1;
   while(j2<niveau)
   {
       elm_1=elm_1+(pow(2,niveau));
       j2++;
   }
   for (int i=0;i<elm_1;i++) //ON DEFINIT NIVEAU-1
{

     cout<<j<<endl;
    // Path=T[i];
     Path=array1[i];
     array=CreerNoeud(Path);
     array1[j]=array[0];
     array1[j+1]=array[1];
     j+=2;


}

   int puis=NbreIndiceMedian-(pow(2,niveau)+1);
   cout<<"puis"<<puis<<endl;
   int i1=elm_1;
   for (int i=puis;i<NbreIndiceMedian-1;i++)
    {

    string P=array1[i1];
    cout<<P<<endl;
    P +="/toto1.txt";

    const char* c= P.c_str(); //Convertion du Qstring to char*
    //creation de fichier de points
    ofstream f(c);
    if (!f.is_open())
        cout << " Impossible d'ouvrir le fichier en écriture !" << endl;
    else
    {



            cout<<median[i]<<"kkkkkk"<<median[i+1]<<endl;
            for (int k=median[i]; k <median[i+1]; k++){

             f << v1[k][0] <<""<<v1[k][1]<<" "<<v1[k][2]<<"\n";}




        f.close();
    }
        i1++;
        P="/0";}
    //createtree(v1);
    cout<<"fait alhamdo lilah"<<endl;
    NoeudKd *p1;
    Voxel v;
    P=new NoeudKd[NbreVoxel];
    cout<<NbreVoxel<<endl;
    for (int i=0;i<elm;i++)
    {
         P[i].setpath(array1[i]);
         P[i].setVoxel(tabvoxel[i]);
          //P[i].voxel(tabvoxel[i].getDebut(),tabvoxel[i].getFin());

        //P=p1;
        cout<<"element1 du tableau"<<tabvoxel[i].getDebut().getX()<<endl;
        cout<<"element1 du tableau"<<P[i].getvoxel().getDebut().getX()<<endl;
        cout<<"element2 du tableau"<<tabvoxel[i].getDebut().getY()<<endl;
        cout<<"element2 du tableau"<<P[i].getvoxel().getDebut().getY()<<endl;
        //cout<<"element3 du tableau"<<tabvoxel[i].getDebut().getZ()<<endl;
        //cout<<"element3 du tableau"<<P[i].getvoxel().getDebut().getZ()<<endl;
        /*cout<<P[i].getvoxel().getFin().getX()<<endl;
        cout<<P[i].getvoxel().getFin().getY()<<endl;
        cout<<P[i].getvoxel().getFin().getZ()<<endl;

    }


}*/




NoeudKd* KdTree::construire1()
    {
    // Code spécifique au kd-tree

    string path="E:/araignee.ply";
    int lignes = calculPoints(path);
    double** v1;
    int NbreIndiceMedian=0;
    int NbreVoxel;
    int k1=0;




    while (3>=k1)
    {
    NbreIndiceMedian=NbreIndiceMedian+(pow(2,k1)+1);
    k1++;
    }

    while (3>=k1)
    {
    NbreVoxel=NbreVoxel+(pow(2,k1));
    k1++;
    }

    int nbremedian=(pow(2,3)-1);
    int *indiceplanmedian=new int[nbremedian];
    tabpointmedian=new Point3D[nbremedian];


    int *median=new int[NbreIndiceMedian];
    cout<<NbreIndiceMedian<<endl;
    cout<<nbremedian<<endl;

    median= CalculIndiceMedian(path,3);
    indiceplanmedian=CalculIndicePlanMedian(path,3);

    v1=lirefichierply(path,lignes);


    tabvoxel=new Voxel[NbreVoxel];
    cout<<"nbre de voxel"<<endl;
    int n=0;
    int i=1;
    int i2=1;
    int i3=0;
    while ( i<NbreIndiceMedian ){
    if ( median[i]!=0 )
    {   cout<<median[i]<<" "<<endl;
        v1=triePoint(median[i],median[i-1],n,v1);// trie par colonne j jusqu'a l'element d
        tabvoxel[i3]=calculvoxel(v1,median[i-1],median[i]);
        if(i2<=nbremedian)
        {
        //cout<<indiceplanmedian[i2-1]<<"::::lah isahal"<<endl;
       // point.setX(0);
        point.setX(v1[indiceplanmedian[i2-1]][0]);
        point.setY(v1[indiceplanmedian[i2-1]][1]);
        point.setZ(v1[indiceplanmedian[i2-1]][2]);
        tabpointmedian[i2]=point;

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

    cout<<"hamdolah"<<endl;
    //Creation de l'Arborescente Binaire
    string Path="E:/Test/Z/Z1";
    string* T;

    T=CreerNoeud(Path);
    string *array=new string[2];
    string *array1=new string[14];//ON DEFINIT LE NIVEAU DE L'ARBORESCENCE .
    array1[0]=T[0];
    array1[1]=T[1];

  // cout<<T[0]<<""<<T[1]<<endl;
   int j=2;
   for (int i=0;i<6;i++) //ON DEFINIT NIVEAU-1
{

     cout<<j<<endl;
    // Path=T[i];
     Path=array1[i];
     array=CreerNoeud(Path);
     array1[j]=array[0];
     array1[j+1]=array[1];
     j+=2;


}

   int puis=NbreIndiceMedian-(pow(2,3)+1);
   cout<<"fffff"<<puis<<endl;
   int i1=6;
   for (int i=puis;i<NbreIndiceMedian-1;i++)
    {

    string P=array1[i1];
    cout<<P<<endl;
    P +="/toto1.txt";

    const char* c= P.c_str(); //Convertion du Qstring to char*
    //creation de fichier de points
    ofstream f(c);
    if (!f.is_open())
        cout << " Impossible d'ouvrir le fichier en écriture !" << endl;
    else
    {



            cout<<median[i]<<"kkkkkk"<<median[i+1]<<endl;
            for (int k=median[i]; k <median[i+1]; k++){

             f << v1[k][0] <<" "<<v1[k][1]<<" "<<v1[k][2]<<"\n";}




        f.close();
    }
        i1++;
        P="/0";}
    //createtree(v1);
    cout<<"fait alhamdo lilah"<<endl;
    NoeudKd p1;
    NoeudKd* P;
    P=new NoeudKd[NbreVoxel];
    cout<<NbreVoxel<<endl;
    for (int i=0;i<14;i++)
    {
        P[i].setpath(array1[i]);
        P[i].setVoxel(tabvoxel[i]);

        cout<<P[i].getpath()<<endl;

        cout<<"element1 du tableau"<<tabvoxel[i].getDebut().getX()<<endl;
        cout<<"element1 du tableau"<<P[i].getVoxel().getDebut().getX()<<endl;
        cout<<"element2 du tableau"<<tabvoxel[i].getDebut().getY()<<endl;
        cout<<"element2 du tableau"<<P[i].getVoxel().getDebut().getY()<<endl;
        cout<<"element3 du tableau"<<tabvoxel[i].getDebut().getZ()<<endl;
        cout<<"element3 du tableau"<<P[i].getVoxel().getDebut().getZ()<<endl;
        /*cout<<P[i].getvoxel().getFin().getX()<<endl;
        cout<<P[i].getvoxel().getFin().getY()<<endl;
        cout<<P[i].getvoxel().getFin().getZ()<<endl;*/

    }
    return P;
}


void KdTree::construire() {

}


Point* KdTree::requete(const Point &centre, double distance) const
{
    // requête sur un voisinage
}

Point* KdTree::requete(const Voxel &conteneur) const {
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
         while (std::getline(fichier, info) && i<lignes)
         {
             //GotoLine(file, 8);

             {
                 if ( atoi(info.c_str()))  //check that the input is number
                     // if (i>8 && i<963)
                 {
                     v1[i][0] = strtod (info.c_str(), &pEnd);
                     v1[i][1]= strtod (pEnd, &pEnd1);
                     v1[i][2] = strtod (pEnd1, NULL);

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



string* KdTree::CreerNoeud(string P){


    QString Path=QString(P.c_str());
    QString Path1=Path;
    QString Path2=Path;
    stringstream out1,out2;

    string *T= new string[2];


     Path1=Path+"/Z";
     Path2=Path+"/Z";

     int j=1;
     out1<<j;
     out2<<j+1;
     std::cout <<out1.str();
     Path1+= QString(out1.str().c_str());
     Path2+=QString(out2.str().c_str());

     out1.str("");
     out2.str("");


        QDir mdir(Path1);
        QDir mdir1(Path2);


        if(!mdir.exists(Path1) && !mdir1.exists(Path2) )
        {
            mdir.mkpath(Path1);
            mdir1.mkpath(Path2);
            qDebug()<<"Created";
        }
        else
        {
            qDebug()<<"Already exists";
        }
        T[0]=Path1.toStdString();
        T[1]=Path2.toStdString();

        //cout<<T[0]<<""<<T[1]<<endl;

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

         if (v[i][2]>min3)
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

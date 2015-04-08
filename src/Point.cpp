/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

/* Ce fichier contient l'implémentation des méthodes de la classe Point. */


#include <QCoreApplication>
#include<iostream>
#include<fstream>
#include <string>
#include "../include/Point.h"
using namespace std;

/* Constructeurs */

Point::Point() : Point3D()
{
    //ctor
}

Point::Point(double x, double y, double z) : Point3D(x, y, z) {}

Point::~Point()
{
    //dtor
}

Point Point::readPly(string Path,int line)
{
    Point result;
    ifstream fichier (Path.c_str(),ios::in);

    double** v1;
    string str;
    int i=0;
    char* pEnd;
    char* pEnd1;
    double d1, d2, d3;

    if(fichier)  // si l'ouverture a réussi
    {
        string info;
        getline(fichier, info);
        if (info=="ply")
            cout << "le fichier ouvert est un fichier .ply" << endl;


        while (std::getline(fichier, info))
        {
            //GotoLine(file, 8);
            if(i==line)
            {
                if ( atoi(info.c_str()))  //check that the input is number
                    // if (i>8 && i<963)
                {
                    result.m_x = strtod (info.c_str(), &pEnd);
                    result.m_y = strtod (pEnd, &pEnd1);
                    result.m_z = strtod (pEnd1, NULL);

                    cout <<result.m_x<<" "<<result.m_y<<" "<<result.m_z<< endl;


                }


                break;
            }
            i++;
        }
       /* if( result==NULL){
            cout<<"la ligne %d n'existe pas dans le fichier"<<line<<endl;
        }*/

        fichier.close();  // on ferme le fichier
    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    return result;

}

Point readPlyBinaire(std::string Path,int line)
{}
Point readTxt(std::string Path,int line)
{}


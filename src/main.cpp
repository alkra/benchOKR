/* ©ENSG 2015
 * École nationale des sciences géographiques
 * 6-8 avenue Blaise Pascal
 * Cité Descartes - Champs-sur-Marne
 * 77455 MARNE-LA-VALLÉE CEDEX 2
 * FRANCE */

#include <iostream>
#include<string>
using namespace std;

#include "../include/Point.h"


int main(int argc, char** argv)
{
    Point p;
    string Path="E:/araignee.ply";
    p=p.readPly(Path,13);
}

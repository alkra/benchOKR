#include <QtGui/QApplication>
#include "Projet_Geomatique.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Projet_Geomatique projet_geomatique;
    projet_geomatique.show();
    return app.exec();
}

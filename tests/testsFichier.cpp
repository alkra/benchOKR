#include "../include/Fichier.h"

#include <QDebug>

bool Fichier_test_ajout_point(char *wd) {
    bool res = true;
    qDebug() << "Test n° " << 1 << " : Ajout d'un point dans un fichier." << endl;

    Point monPoint(1, 0.1, 0.01);
    Fichier monFichier;

    qDebug() << "Ajout du point (" << monPoint.getX()
             << ", " << monPoint.getY()
             << ", " << monPoint.getZ()
             << ")" << endl;
    qDebug() << "au fichier " << wd << "/Fichier.txt" << endl;

    if(monFichier.ouvrir("Fichier.txt", QIODevice::Append | QIODevice::Text)) {
        qDebug() << "L'ouverture a réussi." << endl;
    } else if(monFichier.ouvrir("Fichier.txt", QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Le fichier a été créé ; l'ouverture a réussi." << endl;
    } else {
        qDebug() << "L'ouverture a échoué. " << wd << endl;
        res = false;
    }

    if(res) {
        monFichier.ajoutPoint(monPoint);

        qDebug() << "L'écriture a été effectuée. Veuillez vérifier." << endl;
    }
    return res;
}

bool Fichier_test_nombre_points() {
    bool res = true;
    QString fichier("../../donneeTestDIAS/SalamandreCloud.txt");
    qDebug() << "Test n° " << 2 << " : lecture du nombre de points.";
    qDebug() << "Fichier : " << fichier;

    // ouverture du fichier
    Fichier f;
    if(!f.ouvrir(fichier, QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "ÉCHEC DE L'OUVERTURE DU FICHIER "<< fichier;
        return false;
    }

    // lecture du nombre de lignes
    long nbLignes = f.getNbPoints();
    qDebug() << "Nb lignes : " << nbLignes;

    return res;
}

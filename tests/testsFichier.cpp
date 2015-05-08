#include "../include/Fichier.h"

#include <QDebug>
#include <QDir>

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

bool Fichier_test_calculer_voxel() {
    qDebug() << "Test n° "<< 3 << " calcul du voxel d'un fichier.";

    // ouverture du fichier
    QString fichier("./calcVox");
    Fichier f;
    if(!f.ouvrir(fichier, QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "ÉCHEC DE L'OUVERTURE DU FICHIER "<< fichier;
        return false;
    }
    qDebug() << "Écriture des points tests :";
    Point p1(0, 0, 0), p2(1, 1, 1), p3(2, 2, 2), p4(-1, 1, 1);
    f.ajoutPoint(p1);
    qDebug() << p1.toQString();
    f.ajoutPoint(p2);
    qDebug() << p2.toQString();
    f.ajoutPoint(p3);
    qDebug() << p3.toQString();
    f.ajoutPoint(p4);
    qDebug() << p4.toQString();

    // réouverture du fichier
    if(!f.rouvrir(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "ÉCHEC DE L'OUVERTURE DU FICHIER "<< fichier;
        return false;
    }
    f.calculerVoxel();
    Voxel v = f.getVoxel();
    qDebug() << "Voxel : " << v.getDebut().toQString() << " x "
             << v.getFin().toQString();

    // supression du fichier
    QDir courant(".");
    courant.remove(fichier);

    // validation
    if(v.getDebut().getX() == -1
            && v.getDebut().getY() == 0
            && v.getDebut().getZ() == 0
            && v.getFin().getX() == 2
            && v.getFin().getY() == 2
            && v.getFin().getZ() == 2) {
        qDebug("OK");
        return true;
    } else {
        qDebug("Faux !");
        return false;
    }
}

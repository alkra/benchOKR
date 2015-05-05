#include "testsVoxel.h"

bool Voxel_test_creation() {
    bool result = true;
    qDebug() << "Test n° " << 1 << " : Création d'un voxel." << endl;

    qDebug() << "Test n° " << 1 << "." << 1 << " : Création du voxel." << endl;
    Voxel test(0, 0, 0, 1, 1, 1);
    try {
        test.getDebut();
        qDebug() << "créé" << endl;
    } catch(...) { result = false; }

    qDebug() << "Test n° " << 1 << "." << 2 << " : Accès au X du premier point." << endl;
    qDebug() << test.getDebut().getX() << " doit valoir " << 0 << endl;
    if(test.getDebut().getX() != 0) {
        result = false;
    }

    qDebug() << "Test n° " << 1 << "." << 3 << " : Mutation du Z du deuxième point." << endl;
    qDebug() << "On initialise à " << 3 << " le z du deuxième point." << endl;
    Point3D fin = test.getFin();
    fin.setZ(3);
    test.setFin(fin);
    qDebug() << test.getFin().getZ() << " doit valoir " << 3 << endl;
    if(test.getFin().getZ() != 3) {
        result = false;
    }

    return result;
}


bool Voxel_test_intersection() {
    bool result = true;

    qDebug() << "Test n° " << 2 << " Intersection d'un voxel." << endl;
    Voxel test(0, 0, 0, 10, 10, 10);
    qDebug() << "Voxel " << test.getDebut().getX() << " "
        << test.getDebut().getY() << " "
        << test.getDebut().getZ() << " "
        << test.getFin().getX() << " "
        << test.getFin().getY() << " "
        << test.getFin().getZ() << endl;

    Point test1(-5, -5, -5),
            test2(5, 5, 5),
            test3(5, -5, -5),
            test4(-5, -5, 5),
            test5(0, 1, 1);


    qDebug() << "Point n° " << 1 << " : " << test1.getX() << " "
        << test1.getY() << " " << test1.getZ() << endl;
    if(test.intersecte(test1)) {
        qDebug() << "Intersecte largement. Faux.";
        result = false;
    } else {
        qDebug() << "N'intersecte pas. Vrai.";
    }

    qDebug() << "Point n° " << 2 << " : " << test2.getX() << " "
        << test2.getY() << " " << test2.getZ() << endl;
    if(test.intersecte(test2)) {
        qDebug() << "Intersecte largement. Vrai.";
    } else {
        qDebug() << "N'intersecte pas. Faux.";
        result = false;
    }

    qDebug() << "Point n° " << 3 << " : " << test3.getX() << " "
        << test3.getY() << " " << test3.getZ() << endl;
    if(test.intersecte(test3)) {
        qDebug() << "Intersecte largement. Faux.";
        result = false;
    } else {
        qDebug() << "N'intersecte pas. Vrai.";
    }

    qDebug() << "Point n° " << 4 << " : " << test4.getX() << " "
        << test4.getY() << " " << test4.getZ() << endl;
    if(test.intersecte(test4)) {
        qDebug() << "Intersecte largement. Faux.";
        result = false;
    } else {
        qDebug() << "N'intersecte pas. Vrai.";
    }

    qDebug() << "Point n° " << 5 << " : " << test5.getX() << " "
        << test5.getY() << " " << test5.getZ() << endl;
    if(test.intersecte(test5)) {
        qDebug() << "Intersecte largement. Vrai.";
    } else {
        qDebug() << "N'intersecte pas largement. Faux.";
        result = false;
    }
    if(test.intersecte(test5, true)) {
        qDebug() << "Intersecte strictement. Faux.";
        result = false;
    } else {
        qDebug() << "N'intersecte pas strictement. Vrai.";
    }

    return result;
}


bool Voxel_test_double_intersection() {
    bool res = true;
    Voxel un(0, 0, 0, 10, 10, 10), deux(2, 2, 2, 20, 6, 6), trois(-1, -1, -1, -3, -3, -3);

    qDebug() << "Test n° " << 3 << " Intersection de deux voxels." << endl;
    qDebug() << "Test n° " << 3 << "." << 1 << endl;
    qDebug() << "Voxel : (" << un.getDebut().getX() << ", "
             << un.getDebut().getY() << ", "
             << un.getDebut().getZ() << ")x("
             << un.getFin().getX() << ", "
             << un.getFin().getY() << ", "
             << un.getFin().getZ() << ")" << endl;
    qDebug() << "inter : (" << trois.getDebut().getX() << ", "
             << trois.getDebut().getY() << ", "
             << trois.getDebut().getZ() << ")x("
             << trois.getFin().getX() << ", "
             << trois.getFin().getY() << ", "
             << trois.getFin().getZ() << ")" << endl;
    if(Voxel::intersecte(un, trois)) {
        qDebug() << "est non vide. C'est faux !" << endl;
        res = false;
    } else {
        qDebug() << "est vide. C'est bon." << endl;
    }

    qDebug() << "Test n° " << 3 << "." << 2 << endl;
    qDebug() << "Voxel : (" << un.getDebut().getX() << ", "
             << un.getDebut().getY() << ", "
             << un.getDebut().getZ() << ")x("
             << un.getFin().getX() << ", "
             << un.getFin().getY() << ", "
             << un.getFin().getZ() << ")" << endl;
    qDebug() << "inter : (" << deux.getDebut().getX() << ", "
             << deux.getDebut().getY() << ", "
             << deux.getDebut().getZ() << ")x("
             << deux.getFin().getX() << ", "
             << deux.getFin().getY() << ", "
             << deux.getFin().getZ() << ")" << endl;
    if(Voxel::intersecte(un, deux)) {
        qDebug() << "est non vide. C'est bon." << endl;
    } else {
        qDebug() << "est vide. C'est faux !" << endl;
        res = false;
    }

    return res;
}

bool Voxel_test_volume() {
    bool res = true;
    Voxel un(0, 0, 0, 1, 1, 1), deux(-1, -1, -1, 1, 1, 1),
            trois(1, 1, 1, -1, -1, -1), quatre(-4, -3, -2, 1, 5, 6);
    qDebug() << "Test n° " << 4 << " : Volume de voxels." << endl;

    qDebug() << "Voxel : (" << un.getDebut().getX() << ", "
             << un.getDebut().getY() << ", "
             << un.getDebut().getZ() << ")x("
             << un.getFin().getX() << ", "
             << un.getFin().getY() << ", "
             << un.getFin().getZ() << ")" << endl;
    qDebug() << "Volume : " << un.volume() << endl;
    if(un.volume() == 1) { qDebug() << "OK" << endl; } else {
        qDebug() << "KO" << endl << endl;
        res = false;
    }

    qDebug() << "Voxel : (" << deux.getDebut().getX() << ", "
             << deux.getDebut().getY() << ", "
             << deux.getDebut().getZ() << ")x("
             << deux.getFin().getX() << ", "
             << deux.getFin().getY() << ", "
             << deux.getFin().getZ() << ")" << endl;
    qDebug() << "Volume : " << deux.volume() << endl << endl;
    if(deux.volume() == 8) { qDebug() << "OK" << endl; } else {
        qDebug() << "KO" << endl << endl;
        res = false;
    }

    qDebug() << "Voxel : (" << trois.getDebut().getX() << ", "
             << trois.getDebut().getY() << ", "
             << trois.getDebut().getZ() << ")x("
             << trois.getFin().getX() << ", "
             << trois.getFin().getY() << ", "
             << trois.getFin().getZ() << ")" << endl;
    qDebug() << "Volume : " << trois.volume() << endl << endl;
    if(trois.volume() == 8) { qDebug() << "OK" << endl; } else {
        qDebug() << "KO" << endl << endl;
        res = false;
    }

    qDebug() << "Voxel : (" << quatre.getDebut().getX() << ", "
             << quatre.getDebut().getY() << ", "
             << quatre.getDebut().getZ() << ")x("
             << quatre.getFin().getX() << ", "
             << quatre.getFin().getY() << ", "
             << quatre.getFin().getZ() << ")" << endl;
    qDebug() << "Volume : " << quatre.volume() << endl << endl;
    if(quatre.volume() == 320) { qDebug() << "OK" << endl; } else {
        qDebug() << "KO" << endl << endl;
        res = false;
    }

    return res;
}

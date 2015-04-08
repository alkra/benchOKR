#include "testsVoxel.h"

bool Voxel_test_creation(std::ostream out) {
    bool result = true;
    out << "Test n° " << 1 << " : Création d'un voxel." << std::endl;

    out << "Test n° " << 1 << "." << 1 << " : Création du voxel." << std::endl;
    Voxel test(0, 0, 0, 1, 1, 1);
    if(test.getDebut()) {
        out << "créé" << std::endl;
    } else { result = false; }

    out << "Test n° " << 1 << "." << 2 << " : Accès au X du premier point." << std::endl;
    out << test.getDebut().getX() << " doit valoir " << 0 << std::endl;
    if(test.getDebut().getX() != 0) {
        result = false;
    }

    out << "Test n° " << 1 << "." << 3 << " : Mutation du Z du deuxième point." << std::endl;
    out << "On initialise à " << 3 << " le z du deuxième point." << std::endl;
    Point3D fin = test.getFin();
    fin.setZ(3);
    test.setFin(fin);
    out << test.getFin().getZ() << " doit valoir " << 3 << std::endl;
    if(test.getFin().getZ() != 3) {
        result = false;
    }

    return result;
}


bool Voxel_test_intersection(std::ostream out) {
    bool result = true;

    out << "Test n° " << 2 << "Intersection d'un voxel." << std::endl;
    Voxel test(0, 0, 0, 10, 10, 10);
    out << "Voxel " << test.getDebut().getX() << " "
        << test.getDebut().getY() << " "
        << test.getDebut().getZ() << " "
        << test.getFin().getX() << " "
        << test.getFin().getY() << " "
        << test.getFin().getZ() << std::endl;

    Point test1(-5, -5, -5),
            test2(5, 5, 5),
            test3(5, -5, -5),
            test4(-5, -5, 5),
            test5(0, 1, 1);

    \
    out << "Point n° " << 1 << " : " << test1.getX() << " "
        << test1.getY() << " " << test1.getZ() << std::endl;
    if(test.intersecte(test1)) {
        out << "Intersecte largement. Faux.";
        result = false;
    } else {
        out << "N'intersecte pas. Vrai.";
    }

    out << "Point n° " << 2 << " : " << test2.getX() << " "
        << test2.getY() << " " << test2.getZ() << std::endl;
    if(test.intersecte(test2)) {
        out << "Intersecte largement. Vrai.";
    } else {
        out << "N'intersecte pas. Faux.";
        result = false;
    }

    out << "Point n° " << 3 << " : " << test3.getX() << " "
        << test3.getY() << " " << test3.getZ() << std::endl;
    if(test.intersecte(test3)) {
        out << "Intersecte largement. Faux.";
        result = false;
    } else {
        out << "N'intersecte pas. Vrai.";
    }

    out << "Point n° " << 4 << " : " << test4.getX() << " "
        << test4.getY() << " " << test4.getZ() << std::endl;
    if(test.intersecte(test4)) {
        out << "Intersecte largement. Faux.";
        result = false;
    } else {
        out << "N'intersecte pas. Vrai.";
    }

    out << "Point n° " << 5 << " : " << test5.getX() << " "
        << test5.getY() << " " << test5.getZ() << std::endl;
    if(test.intersecte(test5)) {
        out << "Intersecte largement. Faux.";
        result = false;
    } else {
        out << "N'intersecte pas largement. Vrai.";
    }
    if(test.intersecte(test5, true)) {
        out << "Intersecte largement. Vrai.";
    } else {
        out << "N'intersecte pas largement. Faux.";
        result = false;
    }
}

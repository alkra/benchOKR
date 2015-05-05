#include "testsVoxel.h"
#include "testsFichier.h"

int main(int argc, char *argv[])
{
    bool res = true;
    res = res && Voxel_test_creation();
    res = res && Voxel_test_intersection();
    res = res && Voxel_test_double_intersection();
    res = res && Fichier_test_ajout_point(argv[0]);
    res = res && Voxel_test_volume();

    if(res) {
        qDebug("=== Tous les tests sont passés ===");
        return 0;
    } else {
        qDebug("****** Des tests ont échoué ******");
        return 1;
    }

    qDebug() << sizeof(Point);
}

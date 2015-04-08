#include "testsVoxel.h"

int main()
{
    bool res = true;
    res = res && Voxel_test_creation();
    res = res && Voxel_test_intersection();

    if(res) {
        qDebug("=== Tous les tests sont passés ===");
        return 0;
    } else {
        qDebug("****** Des tests ont échoué ******");
        return 1;
    }
}

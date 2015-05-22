#include "../include/mainwindow.h"
#include "../include/Fichier.h"
#include "../include/simpleViewer.h"
#include "../include/simpleOctree.h"

#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QProcess>


MainWindow::MainWindow(QApplication *app, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), cloud(NULL), cloudSize(0), bmin(1000, 1000, 1000),
    bmax(-1000, -1000, -1000)
{
    ui->setupUi(this);


    QObject::connect(ui->quitB,SIGNAL(released()),app,SLOT(quit()) );
    QObject::connect(ui->openPB,SIGNAL(released()),this,SLOT(open()) );
    QObject::connect(ui->affichagePB,SIGNAL(released()),this,SLOT(displayCloud()) );
    QObject::connect(ui->requeteSimplePB,SIGNAL(released()), this,SLOT(naiveQuery()));
    QObject::connect(ui->requeteOctreePB,SIGNAL(released()), this,SLOT(octreeQuery()));




}

void MainWindow::dropCloud() {
    if(cloud != NULL) {
        for(int i = 0 ; i < cloudSize ; i++) {
            delete cloud[i];
        }
        delete cloud;
        cloudSize = 0;
    }
}

void MainWindow::openCloud(const QString &filename) {
    qDebug() << "Loading " << filename;
    const double start = stopwatch();

    Fichier data(filename);

    Point **rawData = data.getPoints();
    qDebug() << "Points loaded in " << stopwatch() - start;

    const double startCount = stopwatch();
    cloudSize = data.getNbPoints();
    qDebug() << cloudSize << " points loaded (+ " << stopwatch() - startCount << " s)";

    const double startConv = stopwatch();
    cloud = new Vec3*[cloudSize];
    bmin = Vec3(1000, 1000, 1000);
    bmax = Vec3(-1000, -1000, -1000);
    for(int i=0 ; i < cloudSize ; i++) {
        cloud[i] = new Vec3(rawData[i]->getX(), rawData[i]->getY(), rawData[i]->getZ());
        delete rawData[i];

        if(cloud[i]->x < bmin.x) bmin.x = cloud[i]->x;
        if(cloud[i]->y < bmin.y) bmin.y = cloud[i]->y;
        if(cloud[i]->z < bmin.z) bmin.z = cloud[i]->z;
        if(cloud[i]->x > bmax.x) bmax.x = cloud[i]->x;
        if(cloud[i]->y > bmax.y) bmax.y = cloud[i]->y;
        if(cloud[i]->z > bmax.z) bmax.z = cloud[i]->z;
    }
    qDebug() << "Points converted in " << stopwatch() - startConv;
    qDebug() << "Voxel : (" << bmin.x << bmin.y << bmin.z << ") x (" << bmax.x << bmax.y << bmax.z << ")";
}

void MainWindow::open(){
    QString fileName = QFileDialog::getOpenFileName(this,"Choisir fichier point","D:/","*.*");
    openCloud(fileName);
}

void MainWindow::displayCloud() {
    qDebug() << "Displaying cloud";
    Viewer *viewer = new Viewer;
    viewer->setWindowTitle("Affichage du nuage");
    //viewer->setParent(this);
    viewer->setFPSIsDisplayed(true);
    viewer->m_afficher = cloud;
    viewer->m_tailleAfficher = cloudSize;
    viewer->echelle = 0.1;
    viewer->decalage = Vec3(0, 0, 0);
    viewer->show();
}

void MainWindow::naiveQuery() {
    std::vector<int> *resultIndex = new std::vector<int>();
    Vec3 qmin(-1, -1, -11), qmax(3, 3, 3);
    qDebug() << "Query on (" << qmin.x<<qmin.y<<qmin.z<<") x ("<<qmax.x<<qmax.y<<qmax.z<<")";

    Vec3 ** source = cloud;

    double start = stopwatch(), stop;
    for(int i=0; i<cloudSize; ++i) {
        if(naivePointInBox(*source[i], qmin, qmax)) {
            resultIndex->push_back(i);
        } else {
            delete source[i];
        }
    }
    stop = stopwatch();

    cloudSize = resultIndex->size();
    qDebug() << "Naive query returned " << cloudSize << " points in " << stop - start;

    start = stopwatch();
    cloud = new Vec3*[cloudSize];
    for(int i = 0 ; i < cloudSize ; ++i) {
        cloud[i] = source[resultIndex->at(i)];
    }
    qDebug() << "Emptied cloud in " << stopwatch() - start;
}

void MainWindow::octreeQuery() {
    /* CONSTRUCTION DE L'OCTREE */
    qDebug() << "Building Octree";
    double start = stopwatch();
    Vec3 origin((bmax.x + bmin.x) /2, (bmax.y + bmin.y)/2, (bmax.z + bmin.z)/2);
    Vec3 half((bmax.x - bmin.x) /2, (bmax.y - bmin.y)/2, (bmax.z - bmin.z)/2);
    qDebug() << "Origin : " << origin.x << origin.y << origin.z;
    qDebug() << "Half-width : " << half.x << half.y << half.z;
    brandonpelfrey::Octree *octree = new brandonpelfrey::Octree(origin, half);
    OctreePoint *octreePoints = NULL;
    init(octree, octreePoints, cloud, cloudSize, bmin, bmax);
    qDebug() << "Built Octree in " << stopwatch() - start;




    /* AFFICHAGE DES VOXELS */
    qDebug() << "Displaying voxels";
    start = stopwatch();
    // Instantiate the viewer.
    Viewer *fenetreBB = new Viewer;
    fenetreBB->setWindowTitle("Centres des boites englobantes");
    //fenetreBB->setParent(this);
    fenetreBB->setFPSIsDisplayed(true);
    fenetreBB->show();


    fenetreBB->echelle = 0.1;
    fenetreBB->decalage = Vec3(0, 0, 0);

    // Get voxels
    std::vector<Vec3*> *a = new std::vector<Vec3*>(); int tailleAfficher;
    octree->getOrigins(*a, tailleAfficher);
    fenetreBB->m_tailleAfficher = tailleAfficher;
    qDebug() << tailleAfficher;

    // Converting points
    fenetreBB->m_afficher = new Vec3*[tailleAfficher];
    for(int i=0 ; i < tailleAfficher ; i++) {
        fenetreBB->m_afficher[i] = a->at(i);
    }
    qDebug() << "Displaying points in " << stopwatch() - start;



    /* REQUÊTES SUR L'OCTREE */
    Vec3 qmin(-1, -1, -11), qmax(3, 3, 3);
    qDebug() << "Query on (" << qmin.x<<qmin.y<<qmin.z<<") x ("<<qmax.x<<qmax.y<<qmax.z<<")";

    start = stopwatch();
    std::vector<OctreePoint*> champDeVision;
    testOctree(octree, qmin, qmax, champDeVision);
    cloudSize = champDeVision.size();
    qDebug() << "Queried octree : got "<< cloudSize << " points in " << stopwatch() - start;

    for(int i = 0 ; i < cloudSize ; i++) {
        cloud[i] = champDeVision[i]->getPosition();
    }
}

// Gestion signal
void MainWindow::displayConsole()
{







}

//void MainWindow::exemple() {

//    qDebug()<<"Et voila on reagit au signal \n";
//    close();

//}

void MainWindow::compute(){
    qDebug()<<"Choix de format...";
    if (ui->binRB->isChecked()) {
        qDebug()<<"Traintement sur fichier Binaire";
    }
    if (ui->textRB->isChecked()) {
        qDebug()<<" Traintement sur fichier Texte";
    }

    qDebug()<<"Fichier choisit : "<<ui->fileNameLE->text();


}



MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QProcess>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QObject::connect(ui->quitB,SIGNAL(released()),this,SLOT(exemple()) );
    QObject::connect(ui->openPB,SIGNAL(released()),this,SLOT(open()) );
    //QObject::connect(ui->computePB,SIGNAL(released()),this,SLOT(compute()) );
   // QObject::connect(ui->consoleTE,SIGNAL(readyReadStandartOutput()), this,SLOT(displayConsole()));
    //QObject::connect(ui->consoleTE,SIGNAL(readyReadStarndartError()), this,SLOT(displayConsole()));




}

void MainWindow::open(){
    QString fileName = QFileDialog::getOpenFileName(this,"Choisir fichier point","D:/","*.*");
    ui->fileNameLE->setText(fileName);

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

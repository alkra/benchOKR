/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOubri;
    QAction *actionClose_all;
    QAction *actionQuit;
    QAction *actionComupe;
    QAction *actionCompute;
    QAction *actionCompute_2;
    QAction *actionCompute_3;
    QAction *actionCompute_4;
    QWidget *centralWidget;
    QLineEdit *fileNameLE;
    QPushButton *openPB;
    QPushButton *quitB;
    QRadioButton *textRB;
    QRadioButton *binRB;
    QTextEdit *consoleTE;
    QPushButton *affichagePB;
    QPushButton *requeteSimplePB;
    QPushButton *requeteOctreePB;
    QMenuBar *menuBar;
    QMenu *menuBenchOKR;
    QMenu *menuEdit;
    QMenu *menuKd_Tree;
    QMenu *menuOctree;
    QMenu *menuR_Tree;
    QMenu *menuDisplay;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(770, 369);
        actionOubri = new QAction(MainWindow);
        actionOubri->setObjectName(QStringLiteral("actionOubri"));
        actionClose_all = new QAction(MainWindow);
        actionClose_all->setObjectName(QStringLiteral("actionClose_all"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionComupe = new QAction(MainWindow);
        actionComupe->setObjectName(QStringLiteral("actionComupe"));
        actionCompute = new QAction(MainWindow);
        actionCompute->setObjectName(QStringLiteral("actionCompute"));
        actionCompute_2 = new QAction(MainWindow);
        actionCompute_2->setObjectName(QStringLiteral("actionCompute_2"));
        actionCompute_3 = new QAction(MainWindow);
        actionCompute_3->setObjectName(QStringLiteral("actionCompute_3"));
        actionCompute_4 = new QAction(MainWindow);
        actionCompute_4->setObjectName(QStringLiteral("actionCompute_4"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        fileNameLE = new QLineEdit(centralWidget);
        fileNameLE->setObjectName(QStringLiteral("fileNameLE"));
        fileNameLE->setGeometry(QRect(10, 30, 301, 21));
        openPB = new QPushButton(centralWidget);
        openPB->setObjectName(QStringLiteral("openPB"));
        openPB->setGeometry(QRect(320, 0, 75, 23));
        quitB = new QPushButton(centralWidget);
        quitB->setObjectName(QStringLiteral("quitB"));
        quitB->setGeometry(QRect(690, 290, 75, 23));
        textRB = new QRadioButton(centralWidget);
        textRB->setObjectName(QStringLiteral("textRB"));
        textRB->setGeometry(QRect(320, 20, 81, 21));
        binRB = new QRadioButton(centralWidget);
        binRB->setObjectName(QStringLiteral("binRB"));
        binRB->setGeometry(QRect(320, 40, 81, 21));
        consoleTE = new QTextEdit(centralWidget);
        consoleTE->setObjectName(QStringLiteral("consoleTE"));
        consoleTE->setGeometry(QRect(0, 220, 771, 71));
        affichagePB = new QPushButton(centralWidget);
        affichagePB->setObjectName(QStringLiteral("affichagePB"));
        affichagePB->setGeometry(QRect(0, 0, 111, 23));
        requeteSimplePB = new QPushButton(centralWidget);
        requeteSimplePB->setObjectName(QStringLiteral("requeteSimplePB"));
        requeteSimplePB->setGeometry(QRect(120, 0, 91, 23));
        requeteOctreePB = new QPushButton(centralWidget);
        requeteOctreePB->setObjectName(QStringLiteral("requeteOctreePB"));
        requeteOctreePB->setGeometry(QRect(220, 0, 91, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 770, 21));
        menuBenchOKR = new QMenu(menuBar);
        menuBenchOKR->setObjectName(QStringLiteral("menuBenchOKR"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuKd_Tree = new QMenu(menuEdit);
        menuKd_Tree->setObjectName(QStringLiteral("menuKd_Tree"));
        menuOctree = new QMenu(menuEdit);
        menuOctree->setObjectName(QStringLiteral("menuOctree"));
        menuR_Tree = new QMenu(menuEdit);
        menuR_Tree->setObjectName(QStringLiteral("menuR_Tree"));
        menuDisplay = new QMenu(menuBar);
        menuDisplay->setObjectName(QStringLiteral("menuDisplay"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuBenchOKR->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuDisplay->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuBenchOKR->addAction(actionOubri);
        menuBenchOKR->addAction(actionClose_all);
        menuBenchOKR->addAction(actionQuit);
        menuEdit->addAction(menuKd_Tree->menuAction());
        menuEdit->addAction(menuOctree->menuAction());
        menuEdit->addAction(menuR_Tree->menuAction());
        menuKd_Tree->addAction(actionComupe);
        menuOctree->addAction(actionCompute_3);
        menuR_Tree->addAction(actionCompute_4);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOubri->setText(QApplication::translate("MainWindow", "Open", 0));
        actionClose_all->setText(QApplication::translate("MainWindow", "Close all", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionComupe->setText(QApplication::translate("MainWindow", "Compute", 0));
        actionCompute->setText(QApplication::translate("MainWindow", "Compute", 0));
        actionCompute_2->setText(QApplication::translate("MainWindow", "Compute", 0));
        actionCompute_3->setText(QApplication::translate("MainWindow", "Compute", 0));
        actionCompute_4->setText(QApplication::translate("MainWindow", "Compute", 0));
        openPB->setText(QApplication::translate("MainWindow", "Ouvrir", 0));
        quitB->setText(QApplication::translate("MainWindow", "Quit", 0));
        textRB->setText(QApplication::translate("MainWindow", "FichierTexte", 0));
        binRB->setText(QApplication::translate("MainWindow", "FichierBinaire", 0));
        affichagePB->setText(QApplication::translate("MainWindow", "AffichageNuage3D", 0));
        requeteSimplePB->setText(QApplication::translate("MainWindow", "Requ\303\252teSimple", 0));
        requeteOctreePB->setText(QApplication::translate("MainWindow", "Requ\303\252teOctree", 0));
        menuBenchOKR->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuKd_Tree->setTitle(QApplication::translate("MainWindow", "Kd-Tree", 0));
        menuOctree->setTitle(QApplication::translate("MainWindow", "Octree", 0));
        menuR_Tree->setTitle(QApplication::translate("MainWindow", "R-Tree", 0));
        menuDisplay->setTitle(QApplication::translate("MainWindow", "Display", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

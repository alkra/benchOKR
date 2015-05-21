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
#include <QtWidgets/QProgressBar>
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
    QWidget *centralWidget;
    QLineEdit *fileNameLE;
    QPushButton *openPB;
    QPushButton *quitB;
    QPushButton *computePB;
    QRadioButton *textRB;
    QRadioButton *binRB;
    QTextEdit *consoleTE;
    QProgressBar *progressPB;
    QMenuBar *menuBar;
    QMenu *menuBenchOKR;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(770, 347);
        actionOubri = new QAction(MainWindow);
        actionOubri->setObjectName(QStringLiteral("actionOubri"));
        actionClose_all = new QAction(MainWindow);
        actionClose_all->setObjectName(QStringLiteral("actionClose_all"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        fileNameLE = new QLineEdit(centralWidget);
        fileNameLE->setObjectName(QStringLiteral("fileNameLE"));
        fileNameLE->setGeometry(QRect(60, 20, 331, 21));
        openPB = new QPushButton(centralWidget);
        openPB->setObjectName(QStringLiteral("openPB"));
        openPB->setGeometry(QRect(430, 20, 75, 23));
        quitB = new QPushButton(centralWidget);
        quitB->setObjectName(QStringLiteral("quitB"));
        quitB->setGeometry(QRect(640, 160, 75, 23));
        computePB = new QPushButton(centralWidget);
        computePB->setObjectName(QStringLiteral("computePB"));
        computePB->setGeometry(QRect(430, 60, 75, 23));
        textRB = new QRadioButton(centralWidget);
        textRB->setObjectName(QStringLiteral("textRB"));
        textRB->setGeometry(QRect(540, 30, 81, 21));
        binRB = new QRadioButton(centralWidget);
        binRB->setObjectName(QStringLiteral("binRB"));
        binRB->setGeometry(QRect(540, 50, 81, 21));
        consoleTE = new QTextEdit(centralWidget);
        consoleTE->setObjectName(QStringLiteral("consoleTE"));
        consoleTE->setGeometry(QRect(0, 220, 771, 71));
        progressPB = new QProgressBar(centralWidget);
        progressPB->setObjectName(QStringLiteral("progressPB"));
        progressPB->setGeometry(QRect(470, 130, 118, 23));
        progressPB->setValue(24);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 770, 21));
        menuBenchOKR = new QMenu(menuBar);
        menuBenchOKR->setObjectName(QStringLiteral("menuBenchOKR"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuBenchOKR->menuAction());
        menuBenchOKR->addAction(actionOubri);
        menuBenchOKR->addAction(actionClose_all);
        menuBenchOKR->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOubri->setText(QApplication::translate("MainWindow", "Open", 0));
        actionClose_all->setText(QApplication::translate("MainWindow", "Close all", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        openPB->setText(QApplication::translate("MainWindow", "Ouvrir", 0));
        quitB->setText(QApplication::translate("MainWindow", "Quit", 0));
        computePB->setText(QApplication::translate("MainWindow", "Traitements", 0));
        textRB->setText(QApplication::translate("MainWindow", "FichierTexte", 0));
        binRB->setText(QApplication::translate("MainWindow", "FichierBinaire", 0));
        menuBenchOKR->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

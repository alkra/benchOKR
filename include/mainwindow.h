#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#ifndef _WIN32
#include <sys/time.h>
#endif

#include "../SimpleOctree/Vec3.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QApplication *app, QWidget *parent = 0);
    ~MainWindow();

    void dropCloud();
    void openCloud(const QString &filename);


public slots:
    //void exemple();
    void open();
    void compute();
    void displayCloud();
    void displayConsole();
    void naiveQuery() ;
    void octreeQuery();



private:
    Ui::MainWindow *ui;
    Vec3 **cloud;
    int cloudSize;
    Vec3 bmin; // bounding box
    Vec3 bmax;

public:
#ifndef _WIN32

    static double stopwatch() // idem as Stopwatch.h
    {
        struct timeval time;
        gettimeofday(&time, 0 );
        return 1.0 * time.tv_sec + time.tv_usec / (double)1e6;
    }

#else

#include <windows.h>
    static double stopwatch()
    {
        unsigned long long ticks;
        unsigned long long ticks_per_sec;
        QueryPerformanceFrequency( (LARGE_INTEGER *)&ticks_per_sec);
        QueryPerformanceCounter((LARGE_INTEGER *)&ticks);
        return ((float)ticks) / (float)ticks_per_sec;
    }

#endif
};

#endif // MAINWINDOW_H

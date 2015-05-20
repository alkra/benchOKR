#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGLViewer/qglviewer.h>

class Viewer : public QGLViewer
{
protected :
  virtual void draw();
  virtual void init();
  virtual QString helpString() const;
};

#endif // MAINWINDOW_H

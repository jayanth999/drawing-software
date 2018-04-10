#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QtOpenGL>
#include <QGLWidget>

class GLWidget : public QGLWidget
{
   Q_OBJECT
public:
   explicit GLWidget(QWidget *parent=0);
   ~GLWidget();
   void initializeGL();
   void paintGL();
   void resize(int w,int h);
   void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);
   void draw3D();
   void draw2D(int t);
   void zoom(QKeyEvent *k);
   float rotx,roty,rotz;
   QPoint lastPos;
   float vertices [20][3];
   float al,bt,gm;
   int facets [10][10];
   float vert2t[20][2],vert2f[20][2],vert2s[20][2];
   int admt[20][20];
   int admf[20][20];
   int adms[20][20];
   int a[400];
   int n,f;
   int m,m1;
   float zf = 1.0;
   float xtr = 0.0,ytr = 0.0,ztr = 0.0;
};

#endif // GLWIDGET_H

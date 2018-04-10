#include "glwidget.h"
#include <QtOpenGL>
#include <GLUT/glut.h>

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
  setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
  rotx = -20.0;
  roty = 30.0;
  rotz = 0.0;

}

GLWidget::~GLWidget(){

}


void GLWidget::initializeGL(){
    qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

}
void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     if(m1==0)
      draw2D(0);
     else if(m1==1)
       draw2D(1);
     else if(m1==2)
      draw2D(2);
    else
      draw3D();

}
void GLWidget::resize(int width,int height){

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *event){
      lastPos = event->pos();
}
void GLWidget::mouseMoveEvent(QMouseEvent *event){
    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();
    if (event->buttons() & Qt::LeftButton)
     { rotx += 180 * dy;
       roty += 180 * dx;
         updateGL();
    }
    else if (event->buttons() & Qt::RightButton)
        { rotx += 180 * dy;
          rotz += 180 * dx;
           updateGL();
    }
            lastPos = event->pos();
}


void GLWidget::draw3D(){
   // glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 // glLoadIdentity();
  
    glBegin(GL_LINES);
            glColor3f( 1.0f, 0.0f, 0.0f );
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(4.0, 0.0, 0.0);
        glEnd();

        glBegin(GL_LINES);
            glColor3f( 0.0f, 1.0f, 0.0f );
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 4.0, 0.0);
        glEnd();

        glBegin(GL_LINES);
            glColor3f( 0.0f, 0.0f, 1.0f );
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 0.0, 4.0);
        glEnd();


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //glTranslatef(0.0, 0.0, -5.0);
  glRotatef( rotx, 1.0, 0.0, 0.0 );
  glRotatef( roty, 0.0, 1.0, 0.0 );
  glRotatef( rotz, 0.0, 0.0, 1.0 );
  
  //glBegin(GL_POLYGON);
   //glColor3f(   0.0,  1.0,  0.0 );
  for (int i = 0; i < f; i++)
  { glLoadName(i);
    glBegin(GL_POLYGON); 
    qglColor(Qt::red);
    for(int j=0; j<a[i] ; j++){
    glVertex3f(vertices[facets[i][j]][0]*zf+xtr,vertices[facets[i][j]][1]*zf+ytr,vertices[facets[i][j]][2]*zf+ztr);
    }
     glEnd();
  }
  
 
  //glFlush();
  //glutSwapBuffers();
}

void GLWidget::draw2D(int type){
  //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
   
   //glRotatef( rotx, 1.0, 0.0, 0.0 );
   //glRotatef( roty, 0.0, 1.0, 0.0 );
   //glRotatef( rotz, 0.0, 0.0, 1.0 );
  if(type==0){
  glBegin(GL_LINES); 
  glColor3f(0.0,  0.0,  1.0 ); //for normal lines
  glLineWidth(5.0f);
  //glVertex2f(0,0);
  //glVertex2f(0,1);
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(admt[i][j]==1)
        {glVertex2f(vert2t[i][0]*zf+xtr,vert2t[i][1]*zf+ytr);
        glVertex2f(vert2t[j][0]*zf+xtr,vert2t[j][1]*zf+ytr);}
    }
  }
  


  
  glColor3f(0.0,  1.0,  1.0 );   // for hidden lines
  glLineWidth(0.1f);
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(admt[i][j]==2)
        {glVertex2f(vert2t[i][0]*zf+xtr,vert2t[i][1]*zf+ytr);
        glVertex2f(vert2t[j][0]*zf+xtr,vert2t[j][1]*zf+ytr);}
    }
  }

glEnd();


  
  //glFlush();
  //glutSwapBuffers();
} //type 0

if(type==1){
  glBegin(GL_LINES);
  
  glColor3f(0.0,  0.0,  1.0 ); //normal lines
 glLineWidth(5.0f);
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(admf[i][j]==1)
        {glVertex2f(vert2f[i][0]*zf+ytr,vert2f[i][1]*zf+ztr);
        glVertex2f(vert2f[j][0]*zf+ytr,vert2f[j][1]*zf+ztr);}
    }
  }


  
  glColor3f(0.0,  1.0,  1.0 ); // hidden lines 
  glLineWidth(0.1f);
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(admf[i][j]==2&&i!=j)
        {glVertex2f(vert2f[i][0]*zf+ytr,vert2f[i][1]*zf+ztr);
        glVertex2f(vert2f[j][0]*zf+ytr,vert2f[j][1]*zf+ztr);}
    }
  }




 
  glEnd();
  //glFlush();
  //glutSwapBuffers();
} //type 1

if(type==2){
  glBegin(GL_LINES);
  glColor3f(0.0,  0.0,  1.0 ); //normal lines
  glLineWidth(5.0f);
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(adms[i][j]==1)
        {glVertex2f(vert2s[i][0]*zf+xtr,vert2s[i][1]*zf+ztr);
        glVertex2f(vert2s[j][0]*zf+xtr,vert2s[j][1]*zf+ztr);}
    }
  }

  
  
  glColor3f(0.0,  1.0,  1.0 ); //hidden lines 
  glLineWidth(0.1f);
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(adms[i][j]==2)
        {glVertex2f(vert2s[i][0]*zf+xtr,vert2s[i][1]*zf+ztr);
        glVertex2f(vert2s[j][0]*zf+xtr,vert2s[j][1]*zf+ztr);}
    }
  }



  
  glEnd();
  //glFlush();
  //glutSwapBuffers();
} 

}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GLWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent * ev);

private:
    Ui::MainWindow *ui;
    GLWidget *glwidget;
    QString filename;

private slots:
    
   void  on_actionGenerate_2d_File_triggered();

   void  on_actionRead_triggered();

   void   on_actionGenerate_3d_file_triggered();

   void   on_action3D_view_triggered();

   void   on_action2D_topview_triggered();

   void   on_action2D_frontview_triggered();

   void   on_action2D_sideview_triggered();

   void on_actionScreenShot_triggered();




};

#endif // MAINWINDOW_H

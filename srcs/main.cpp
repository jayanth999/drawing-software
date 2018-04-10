#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{   QApplication a(argc, argv);
	QSplashScreen *splash = new QSplashScreen;
     splash->setPixmap(QPixmap("/Users/ravijayanth/Desktop/cop4/ui/splash.jpg"));
     splash->show();
    
    MainWindow w;
    w.show();
    splash->finish(&w);
    delete splash;

    return a.exec();
}

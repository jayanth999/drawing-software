/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRead;
    QAction *actionGenerate_2d_File;
    QAction *actionGenerate_3d_file;
    QAction *action3D_view;
    QAction *action2D_topview;
    QAction *action2D_frontview;
    QAction *action2D_sideview;
    QAction *actionScreenShot;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    GLWidget *widget;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuAbout;
    QMenu *menu_View;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(649, 590);
        actionRead = new QAction(MainWindow);
        actionRead->setObjectName(QStringLiteral("actionRead"));
        actionGenerate_2d_File = new QAction(MainWindow);
        actionGenerate_2d_File->setObjectName(QStringLiteral("actionGenerate_2d_File"));
        actionGenerate_3d_file = new QAction(MainWindow);
        actionGenerate_3d_file->setObjectName(QStringLiteral("actionGenerate_3d_file"));
        action3D_view = new QAction(MainWindow);
        action3D_view->setObjectName(QStringLiteral("action3D_view"));
        action2D_topview = new QAction(MainWindow);
        action2D_topview->setObjectName(QStringLiteral("action2D_topview"));
        action2D_frontview = new QAction(MainWindow);
        action2D_frontview->setObjectName(QStringLiteral("action2D_frontview"));
        action2D_sideview = new QAction(MainWindow);
        action2D_sideview->setObjectName(QStringLiteral("action2D_sideview"));
        actionScreenShot = new QAction(MainWindow);
        actionScreenShot->setObjectName(QStringLiteral("actionScreenShot"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new GLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 649, 22));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(menuAbout->sizePolicy().hasHeightForWidth());
        menuAbout->setSizePolicy(sizePolicy1);
        menu_View = new QMenu(menuBar);
        menu_View->setObjectName(QStringLiteral("menu_View"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuBar->addAction(menu_View->menuAction());
        menu_File->addAction(actionRead);
        menu_File->addAction(actionGenerate_2d_File);
        menu_File->addAction(actionGenerate_3d_file);
        menu_File->addAction(actionScreenShot);
        menu_View->addAction(action3D_view);
        menu_View->addAction(action2D_topview);
        menu_View->addAction(action2D_frontview);
        menu_View->addAction(action2D_sideview);
        mainToolBar->addAction(actionRead);
        mainToolBar->addAction(actionGenerate_2d_File);
        mainToolBar->addAction(actionGenerate_3d_file);
        mainToolBar->addAction(action3D_view);
        mainToolBar->addAction(action2D_topview);
        mainToolBar->addAction(action2D_frontview);
        mainToolBar->addAction(action2D_sideview);
        mainToolBar->addAction(actionScreenShot);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Drawing Software", nullptr));
        actionRead->setText(QApplication::translate("MainWindow", "Read", nullptr));
        actionGenerate_2d_File->setText(QApplication::translate("MainWindow", "Generate_2d_File", nullptr));
        actionGenerate_3d_file->setText(QApplication::translate("MainWindow", "Generate_3d_file", nullptr));
        action3D_view->setText(QApplication::translate("MainWindow", "3D_view", nullptr));
        action2D_topview->setText(QApplication::translate("MainWindow", "2D_topview", nullptr));
        action2D_frontview->setText(QApplication::translate("MainWindow", "2D_frontview", nullptr));
        action2D_sideview->setText(QApplication::translate("MainWindow", "2D_sideview", nullptr));
        actionScreenShot->setText(QApplication::translate("MainWindow", "ScreenShot", nullptr));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", nullptr));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", nullptr));
        menu_View->setTitle(QApplication::translate("MainWindow", "&View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

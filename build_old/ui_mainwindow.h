/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QListWidget *listWidget;
    QGroupBox *groupBox;
    QSlider *gridsampling;
    QSlider *contoursampling;
    QLabel *label;
    QLabel *label_2;
    QLabel *contoursamplingvalue;
    QLabel *gridsamplingvalue;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QSlider *slider_lshapes;
    QLabel *label_lshapes;
    QLabel *z_label_3;
    QWidget *tab_2;
    QSlider *slider_lsym;
    QLabel *label_lsym;
    QLabel *z_label_5;
    QSlider *slider_ldepthsym;
    QLabel *z_label_4;
    QLabel *label_ldepthsym;
    QWidget *tab_3;
    QSlider *slider_ldepthisland;
    QLabel *z_label_6;
    QLabel *z_label_7;
    QSlider *slider_lisland;
    QLabel *label_lisland;
    QLabel *label_ldepthisland;
    QWidget *tab_4;
    QSlider *slider_ldepthadj;
    QLabel *z_label_9;
    QLabel *label_ldepthadj;
    QSlider *slider_ladj;
    QLabel *label_ladj;
    QLabel *z_label_10;
    QLabel *label_adjnewcontour;
    QSlider *slider_adjnewcontour;
    QLabel *z_label_8;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1427, 709);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1290, 620, 75, 23));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(1030, 20, 381, 192));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(1030, 440, 391, 131));
        gridsampling = new QSlider(groupBox);
        gridsampling->setObjectName(QString::fromUtf8("gridsampling"));
        gridsampling->setGeometry(QRect(200, 90, 160, 22));
        gridsampling->setMinimum(1);
        gridsampling->setMaximum(40);
        gridsampling->setValue(20);
        gridsampling->setOrientation(Qt::Horizontal);
        contoursampling = new QSlider(groupBox);
        contoursampling->setObjectName(QString::fromUtf8("contoursampling"));
        contoursampling->setGeometry(QRect(30, 90, 160, 22));
        contoursampling->setMinimum(1);
        contoursampling->setMaximum(20);
        contoursampling->setValue(10);
        contoursampling->setOrientation(Qt::Horizontal);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 30, 101, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(250, 30, 101, 20));
        contoursamplingvalue = new QLabel(groupBox);
        contoursamplingvalue->setObjectName(QString::fromUtf8("contoursamplingvalue"));
        contoursamplingvalue->setGeometry(QRect(90, 60, 47, 13));
        gridsamplingvalue = new QLabel(groupBox);
        gridsamplingvalue->setObjectName(QString::fromUtf8("gridsamplingvalue"));
        gridsamplingvalue->setGeometry(QRect(260, 60, 47, 13));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(1040, 590, 171, 19));
        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(1040, 620, 181, 19));
        checkBox_3 = new QCheckBox(centralWidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(1040, 650, 181, 19));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(1030, 240, 391, 181));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        slider_lshapes = new QSlider(tab);
        slider_lshapes->setObjectName(QString::fromUtf8("slider_lshapes"));
        slider_lshapes->setGeometry(QRect(110, 90, 160, 22));
        slider_lshapes->setMinimum(1);
        slider_lshapes->setMaximum(40);
        slider_lshapes->setValue(10);
        slider_lshapes->setOrientation(Qt::Horizontal);
        label_lshapes = new QLabel(tab);
        label_lshapes->setObjectName(QString::fromUtf8("label_lshapes"));
        label_lshapes->setGeometry(QRect(170, 60, 47, 13));
        z_label_3 = new QLabel(tab);
        z_label_3->setObjectName(QString::fromUtf8("z_label_3"));
        z_label_3->setGeometry(QRect(150, 30, 101, 20));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        slider_lsym = new QSlider(tab_2);
        slider_lsym->setObjectName(QString::fromUtf8("slider_lsym"));
        slider_lsym->setGeometry(QRect(30, 90, 160, 22));
        slider_lsym->setMinimum(1);
        slider_lsym->setMaximum(40);
        slider_lsym->setValue(10);
        slider_lsym->setOrientation(Qt::Horizontal);
        label_lsym = new QLabel(tab_2);
        label_lsym->setObjectName(QString::fromUtf8("label_lsym"));
        label_lsym->setGeometry(QRect(90, 60, 47, 13));
        z_label_5 = new QLabel(tab_2);
        z_label_5->setObjectName(QString::fromUtf8("z_label_5"));
        z_label_5->setGeometry(QRect(50, 30, 131, 20));
        slider_ldepthsym = new QSlider(tab_2);
        slider_ldepthsym->setObjectName(QString::fromUtf8("slider_ldepthsym"));
        slider_ldepthsym->setGeometry(QRect(200, 90, 160, 22));
        slider_ldepthsym->setMinimum(1);
        slider_ldepthsym->setMaximum(40);
        slider_ldepthsym->setValue(10);
        slider_ldepthsym->setOrientation(Qt::Horizontal);
        z_label_4 = new QLabel(tab_2);
        z_label_4->setObjectName(QString::fromUtf8("z_label_4"));
        z_label_4->setGeometry(QRect(230, 30, 141, 21));
        label_ldepthsym = new QLabel(tab_2);
        label_ldepthsym->setObjectName(QString::fromUtf8("label_ldepthsym"));
        label_ldepthsym->setGeometry(QRect(260, 60, 47, 13));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        slider_ldepthisland = new QSlider(tab_3);
        slider_ldepthisland->setObjectName(QString::fromUtf8("slider_ldepthisland"));
        slider_ldepthisland->setGeometry(QRect(200, 90, 160, 22));
        slider_ldepthisland->setMinimum(1);
        slider_ldepthisland->setMaximum(40);
        slider_ldepthisland->setValue(10);
        slider_ldepthisland->setOrientation(Qt::Horizontal);
        z_label_6 = new QLabel(tab_3);
        z_label_6->setObjectName(QString::fromUtf8("z_label_6"));
        z_label_6->setGeometry(QRect(240, 30, 121, 20));
        z_label_7 = new QLabel(tab_3);
        z_label_7->setObjectName(QString::fromUtf8("z_label_7"));
        z_label_7->setGeometry(QRect(70, 30, 101, 20));
        slider_lisland = new QSlider(tab_3);
        slider_lisland->setObjectName(QString::fromUtf8("slider_lisland"));
        slider_lisland->setGeometry(QRect(30, 90, 160, 22));
        slider_lisland->setMinimum(1);
        slider_lisland->setMaximum(40);
        slider_lisland->setValue(10);
        slider_lisland->setOrientation(Qt::Horizontal);
        label_lisland = new QLabel(tab_3);
        label_lisland->setObjectName(QString::fromUtf8("label_lisland"));
        label_lisland->setGeometry(QRect(90, 60, 47, 13));
        label_ldepthisland = new QLabel(tab_3);
        label_ldepthisland->setObjectName(QString::fromUtf8("label_ldepthisland"));
        label_ldepthisland->setGeometry(QRect(260, 60, 47, 13));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        slider_ldepthadj = new QSlider(tab_4);
        slider_ldepthadj->setObjectName(QString::fromUtf8("slider_ldepthadj"));
        slider_ldepthadj->setGeometry(QRect(190, 60, 160, 22));
        slider_ldepthadj->setMinimum(1);
        slider_ldepthadj->setMaximum(40);
        slider_ldepthadj->setValue(10);
        slider_ldepthadj->setOrientation(Qt::Horizontal);
        z_label_9 = new QLabel(tab_4);
        z_label_9->setObjectName(QString::fromUtf8("z_label_9"));
        z_label_9->setGeometry(QRect(230, 0, 121, 20));
        label_ldepthadj = new QLabel(tab_4);
        label_ldepthadj->setObjectName(QString::fromUtf8("label_ldepthadj"));
        label_ldepthadj->setGeometry(QRect(250, 30, 47, 13));
        slider_ladj = new QSlider(tab_4);
        slider_ladj->setObjectName(QString::fromUtf8("slider_ladj"));
        slider_ladj->setGeometry(QRect(20, 60, 160, 22));
        slider_ladj->setMinimum(1);
        slider_ladj->setMaximum(40);
        slider_ladj->setValue(10);
        slider_ladj->setOrientation(Qt::Horizontal);
        label_ladj = new QLabel(tab_4);
        label_ladj->setObjectName(QString::fromUtf8("label_ladj"));
        label_ladj->setGeometry(QRect(80, 30, 47, 13));
        z_label_10 = new QLabel(tab_4);
        z_label_10->setObjectName(QString::fromUtf8("z_label_10"));
        z_label_10->setGeometry(QRect(60, 0, 101, 20));
        label_adjnewcontour = new QLabel(tab_4);
        label_adjnewcontour->setObjectName(QString::fromUtf8("label_adjnewcontour"));
        label_adjnewcontour->setGeometry(QRect(150, 110, 47, 13));
        slider_adjnewcontour = new QSlider(tab_4);
        slider_adjnewcontour->setObjectName(QString::fromUtf8("slider_adjnewcontour"));
        slider_adjnewcontour->setGeometry(QRect(90, 130, 160, 22));
        slider_adjnewcontour->setMinimum(1);
        slider_adjnewcontour->setMaximum(40);
        slider_adjnewcontour->setValue(5);
        slider_adjnewcontour->setOrientation(Qt::Horizontal);
        z_label_8 = new QLabel(tab_4);
        z_label_8->setObjectName(QString::fromUtf8("z_label_8"));
        z_label_8->setGeometry(QRect(120, 80, 131, 20));
        tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralWidget);
        groupBox->raise();
        pushButton->raise();
        listWidget->raise();
        checkBox->raise();
        checkBox_2->raise();
        checkBox_3->raise();
        tabWidget->raise();
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Sampling", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Contour Sampling", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Grid Sampling", nullptr));
        contoursamplingvalue->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        gridsamplingvalue->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Show sampled points on grid", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "Show sampled points on contour", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "Show bounding boxes", nullptr));
        label_lshapes->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        z_label_3->setText(QCoreApplication::translate("MainWindow", "Lambda Shapes", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Border Cycle", nullptr));
        label_lsym->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        z_label_5->setText(QCoreApplication::translate("MainWindow", "Lambda Symmetrical Parts", nullptr));
        z_label_4->setText(QCoreApplication::translate("MainWindow", "Lambda Depth Symmetrical", nullptr));
        label_ldepthsym->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Symmetrical Limbs", nullptr));
        z_label_6->setText(QCoreApplication::translate("MainWindow", "Lambda Depth Island", nullptr));
        z_label_7->setText(QCoreApplication::translate("MainWindow", "Lambda Islands", nullptr));
        label_lisland->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_ldepthisland->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Island Cycle", nullptr));
        z_label_9->setText(QCoreApplication::translate("MainWindow", "Lambda Depth Adjacent", nullptr));
        label_ldepthadj->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_ladj->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        z_label_10->setText(QCoreApplication::translate("MainWindow", "Lambda Adjacent", nullptr));
        label_adjnewcontour->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        z_label_8->setText(QCoreApplication::translate("MainWindow", "Lambda Adjacent Contour", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Adjacent Cycle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

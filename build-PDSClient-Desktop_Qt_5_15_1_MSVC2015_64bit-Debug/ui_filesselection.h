/********************************************************************************
** Form generated from reading UI file 'filesselection.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESSELECTION_H
#define UI_FILESSELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilesSelection
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FilesSelection)
    {
        if (FilesSelection->objectName().isEmpty())
            FilesSelection->setObjectName(QString::fromUtf8("FilesSelection"));
        FilesSelection->resize(800, 600);
        centralwidget = new QWidget(FilesSelection);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        FilesSelection->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FilesSelection);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        FilesSelection->setMenuBar(menubar);
        statusbar = new QStatusBar(FilesSelection);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        FilesSelection->setStatusBar(statusbar);

        retranslateUi(FilesSelection);

        QMetaObject::connectSlotsByName(FilesSelection);
    } // setupUi

    void retranslateUi(QMainWindow *FilesSelection)
    {
        FilesSelection->setWindowTitle(QCoreApplication::translate("FilesSelection", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilesSelection: public Ui_FilesSelection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESSELECTION_H

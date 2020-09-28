/********************************************************************************
** Form generated from reading UI file 'filesselection.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESSELECTION_H
#define UI_FILESSELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilesSelection
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QWidget *toolbarWidget;
    QLabel *labelWidget;
    QWidget *mainWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QPushButton *newDocumentButton;
    QSpacerItem *verticalSpacer_2;
    QLabel *fileListLabel;
    QListWidget *fileListWidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FilesSelection)
    {
        if (FilesSelection->objectName().isEmpty())
            FilesSelection->setObjectName(QString::fromUtf8("FilesSelection"));
        FilesSelection->resize(800, 600);
        centralwidget = new QWidget(FilesSelection);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background: white;\n"
"}"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        toolbarWidget = new QWidget(centralwidget);
        toolbarWidget->setObjectName(QString::fromUtf8("toolbarWidget"));
        toolbarWidget->setMinimumSize(QSize(0, 60));
        toolbarWidget->setMaximumSize(QSize(16777215, 60));
        toolbarWidget->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background:#73c259;\n"
"}"));
        labelWidget = new QLabel(toolbarWidget);
        labelWidget->setObjectName(QString::fromUtf8("labelWidget"));
        labelWidget->setGeometry(QRect(0, 0, 91, 60));
        labelWidget->setMinimumSize(QSize(0, 60));
        labelWidget->setMaximumSize(QSize(16777215, 60));
        labelWidget->setStyleSheet(QString::fromUtf8("*{\n"
"font-familiy: Roboto;\n"
"font-size: 20px;\n"
"font:bold;\n"
"color: white;\n"
"}"));
        labelWidget->setMargin(5);

        verticalLayout_2->addWidget(toolbarWidget);

        mainWidget = new QWidget(centralwidget);
        mainWidget->setObjectName(QString::fromUtf8("mainWidget"));
        verticalLayout_4 = new QVBoxLayout(mainWidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        newDocumentButton = new QPushButton(mainWidget);
        newDocumentButton->setObjectName(QString::fromUtf8("newDocumentButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(newDocumentButton->sizePolicy().hasHeightForWidth());
        newDocumentButton->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(newDocumentButton);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);

        fileListLabel = new QLabel(mainWidget);
        fileListLabel->setObjectName(QString::fromUtf8("fileListLabel"));
        fileListLabel->setStyleSheet(QString::fromUtf8("*{\n"
"font-familiy: Roboto;\n"
"font-size: 24px;\n"
"font:bold;\n"
"}"));

        verticalLayout_3->addWidget(fileListLabel);

        fileListWidget = new QListWidget(mainWidget);
        fileListWidget->setObjectName(QString::fromUtf8("fileListWidget"));

        verticalLayout_3->addWidget(fileListWidget);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_2->addWidget(mainWidget);


        verticalLayout->addLayout(verticalLayout_2);

        FilesSelection->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(FilesSelection);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        FilesSelection->setStatusBar(statusbar);

        retranslateUi(FilesSelection);

        QMetaObject::connectSlotsByName(FilesSelection);
    } // setupUi

    void retranslateUi(QMainWindow *FilesSelection)
    {
        FilesSelection->setWindowTitle(QCoreApplication::translate("FilesSelection", "MainWindow", nullptr));
        labelWidget->setText(QCoreApplication::translate("FilesSelection", "PDS Pro", nullptr));
        newDocumentButton->setText(QCoreApplication::translate("FilesSelection", "Nuovo Documento", nullptr));
        fileListLabel->setText(QCoreApplication::translate("FilesSelection", "Lista dei tuoi file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilesSelection: public Ui_FilesSelection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESSELECTION_H

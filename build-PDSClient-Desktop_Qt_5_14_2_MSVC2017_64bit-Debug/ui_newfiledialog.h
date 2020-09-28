/********************************************************************************
** Form generated from reading UI file 'newfiledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWFILEDIALOG_H
#define UI_NEWFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewFileDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QLabel *label;
    QPlainTextEdit *filenameEdit;
    QSplitter *splitter_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewFileDialog)
    {
        if (NewFileDialog->objectName().isEmpty())
            NewFileDialog->setObjectName(QString::fromUtf8("NewFileDialog"));
        NewFileDialog->resize(429, 146);
        verticalLayout_2 = new QVBoxLayout(NewFileDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter = new QSplitter(NewFileDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setMaximumSize(QSize(16777215, 30));
        splitter->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("*{\n"
"font-familiy: Roboto;\n"
"font-size: 16px;\n"
"}"));
        splitter->addWidget(label);
        filenameEdit = new QPlainTextEdit(splitter);
        filenameEdit->setObjectName(QString::fromUtf8("filenameEdit"));
        sizePolicy.setHeightForWidth(filenameEdit->sizePolicy().hasHeightForWidth());
        filenameEdit->setSizePolicy(sizePolicy);
        filenameEdit->setMaximumSize(QSize(16777215, 30));
        splitter->addWidget(filenameEdit);

        verticalLayout->addWidget(splitter);

        splitter_2 = new QSplitter(NewFileDialog);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        buttonBox = new QDialogButtonBox(splitter_2);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        splitter_2->addWidget(buttonBox);

        verticalLayout->addWidget(splitter_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(NewFileDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewFileDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewFileDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewFileDialog);
    } // setupUi

    void retranslateUi(QDialog *NewFileDialog)
    {
        NewFileDialog->setWindowTitle(QCoreApplication::translate("NewFileDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("NewFileDialog", "Nome file: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewFileDialog: public Ui_NewFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWFILEDIALOG_H

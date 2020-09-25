/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QWidget *loginWidget_2;
    QFrame *loginFrame;
    QLabel *loginLabel;
    QLineEdit *loginUsername;
    QLineEdit *loginPassword;
    QPushButton *loginButton;
    QFrame *line;
    QWidget *registrationWidget;
    QFrame *registrationFrame;
    QLineEdit *registrationNickname;
    QLabel *registrationLabel;
    QLineEdit *registrationFirstPassword;
    QLineEdit *registrationUsername;
    QPushButton *registrationButton;
    QLineEdit *registrationSecondPassword;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(800, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background:#73c259;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        loginWidget_2 = new QWidget(centralwidget);
        loginWidget_2->setObjectName(QString::fromUtf8("loginWidget_2"));
        loginWidget_2->setFocusPolicy(Qt::ClickFocus);
        loginFrame = new QFrame(loginWidget_2);
        loginFrame->setObjectName(QString::fromUtf8("loginFrame"));
        loginFrame->setGeometry(QRect(50, 70, 281, 371));
        loginFrame->setStyleSheet(QString::fromUtf8("QFrame{\n"
"	background: 	#ffffff;\n"
"	border-radius: 30px;\n"
"}"));
        loginFrame->setFrameShape(QFrame::StyledPanel);
        loginFrame->setFrameShadow(QFrame::Raised);
        loginLabel = new QLabel(loginFrame);
        loginLabel->setObjectName(QString::fromUtf8("loginLabel"));
        loginLabel->setGeometry(QRect(100, 20, 121, 41));
        loginLabel->setStyleSheet(QString::fromUtf8("*{\n"
"font-familiy: Roboto;\n"
"font-size: 24px;\n"
"font:bold;\n"
"}"));
        loginUsername = new QLineEdit(loginFrame);
        loginUsername->setObjectName(QString::fromUtf8("loginUsername"));
        loginUsername->setGeometry(QRect(20, 120, 241, 31));
        loginUsername->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background: transparent;\n"
"	border:none;\n"
"	color:#717072;\n"
"	border-bottom:1px solid #717072;\n"
"	font-family: Roboto;\n"
"}"));
        loginPassword = new QLineEdit(loginFrame);
        loginPassword->setObjectName(QString::fromUtf8("loginPassword"));
        loginPassword->setGeometry(QRect(20, 210, 241, 31));
        loginPassword->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background: transparent;\n"
"	border:none;\n"
"	color:#717072;\n"
"	border-bottom:1px solid #717072;\n"
"	font-family: Roboto;\n"
"	type: password\n"
"}"));
        loginPassword->setMaxLength(32767);
        loginPassword->setEchoMode(QLineEdit::Password);
        loginButton = new QPushButton(loginFrame);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(80, 300, 121, 51));
        loginButton->setStyleSheet(QString::fromUtf8("\n"
"loginButton{ \n"
"      text-decoration: none; \n"
"      border: none; \n"
"      padding: 12px 40px; \n"
"      font-size: 16px; \n"
"      background-color: green; \n"
"      color: #fff; \n"
"      border-radius: 5px; \n"
"      box-shadow: 7px 6px 28px 1px rgba(0, 0, 0, 0.24); \n"
"      cursor: pointer; \n"
"      outline: none; \n"
"      transition: 0.2s all; \n"
" } \n"
"        /* Adding transformation when the button is active */ \n"
"          \n"
".loginButton:active { \n"
"       transform: scale(0.98); \n"
"       /* Scaling button to 0.98 to its original size */ \n"
"       box-shadow: 3px 2px 22px 1px rgba(0, 0, 0, 0.24); \n"
"        /* Lowering the shadow */ \n"
" } "));
        loginButton->setAutoDefault(false);

        horizontalLayout->addWidget(loginWidget_2);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        registrationWidget = new QWidget(centralwidget);
        registrationWidget->setObjectName(QString::fromUtf8("registrationWidget"));
        registrationFrame = new QFrame(registrationWidget);
        registrationFrame->setObjectName(QString::fromUtf8("registrationFrame"));
        registrationFrame->setGeometry(QRect(40, 30, 301, 451));
        registrationFrame->setStyleSheet(QString::fromUtf8("QFrame{\n"
"	background: 	#ffffff;\n"
"	border-radius: 30px;\n"
"}"));
        registrationFrame->setFrameShape(QFrame::StyledPanel);
        registrationFrame->setFrameShadow(QFrame::Raised);
        registrationNickname = new QLineEdit(registrationFrame);
        registrationNickname->setObjectName(QString::fromUtf8("registrationNickname"));
        registrationNickname->setGeometry(QRect(30, 170, 251, 31));
        registrationNickname->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background: transparent;\n"
"	border:none;\n"
"	color:#717072;\n"
"	border-bottom:1px solid #717072;\n"
"	font-family: Roboto;\n"
"}"));
        registrationLabel = new QLabel(registrationFrame);
        registrationLabel->setObjectName(QString::fromUtf8("registrationLabel"));
        registrationLabel->setGeometry(QRect(100, 20, 121, 41));
        registrationLabel->setStyleSheet(QString::fromUtf8("*{\n"
"font-familiy: Roboto;\n"
"font-size: 24px;\n"
"font:bold;\n"
"}"));
        registrationFirstPassword = new QLineEdit(registrationFrame);
        registrationFirstPassword->setObjectName(QString::fromUtf8("registrationFirstPassword"));
        registrationFirstPassword->setGeometry(QRect(30, 240, 251, 31));
        registrationFirstPassword->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background: transparent;\n"
"	border:none;\n"
"	color:#717072;\n"
"	border-bottom:1px solid #717072;\n"
"	font-family: Roboto;\n"
"}"));
        registrationFirstPassword->setMaxLength(32767);
        registrationFirstPassword->setEchoMode(QLineEdit::Password);
        registrationUsername = new QLineEdit(registrationFrame);
        registrationUsername->setObjectName(QString::fromUtf8("registrationUsername"));
        registrationUsername->setGeometry(QRect(30, 100, 251, 31));
        registrationUsername->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background: transparent;\n"
"	border:none;\n"
"	color:#717072;\n"
"	border-bottom:1px solid #717072;\n"
"	font-family: Roboto;\n"
"}"));
        registrationButton = new QPushButton(registrationFrame);
        registrationButton->setObjectName(QString::fromUtf8("registrationButton"));
        registrationButton->setGeometry(QRect(90, 380, 121, 51));
        registrationButton->setFocusPolicy(Qt::ClickFocus);
        registrationButton->setStyleSheet(QString::fromUtf8("loginButton{ \n"
"      text-decoration: none; \n"
"      border: none; \n"
"      padding: 12px 40px; \n"
"      font-size: 16px; \n"
"      background-color: green; \n"
"      color: #fff; \n"
"      border-radius: 5px; \n"
"      box-shadow: 7px 6px 28px 1px rgba(0, 0, 0, 0.24); \n"
"      cursor: pointer; \n"
"      outline: none; \n"
"      transition: 0.2s all; \n"
" } \n"
"        /* Adding transformation when the button is active */ \n"
"          \n"
".loginButton:active { \n"
"       transform: scale(0.98); \n"
"       /* Scaling button to 0.98 to its original size */ \n"
"       box-shadow: 3px 2px 22px 1px rgba(0, 0, 0, 0.24); \n"
"        /* Lowering the shadow */ \n"
" } "));
        registrationSecondPassword = new QLineEdit(registrationFrame);
        registrationSecondPassword->setObjectName(QString::fromUtf8("registrationSecondPassword"));
        registrationSecondPassword->setGeometry(QRect(30, 310, 251, 31));
        registrationSecondPassword->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	background: transparent;\n"
"	border:none;\n"
"	color:#717072;\n"
"	border-bottom:1px solid #717072;\n"
"	font-family: Roboto;\n"
"}"));
        registrationSecondPassword->setMaxLength(32767);
        registrationSecondPassword->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(registrationWidget);


        horizontalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        loginLabel->setText(QCoreApplication::translate("MainWindow", "Accedi", nullptr));
        loginUsername->setInputMask(QString());
        loginUsername->setText(QString());
        loginUsername->setPlaceholderText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        loginPassword->setInputMask(QString());
        loginPassword->setText(QString());
        loginPassword->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "Accedi", nullptr));
        registrationNickname->setInputMask(QString());
        registrationNickname->setText(QString());
        registrationNickname->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nickname", nullptr));
        registrationLabel->setText(QCoreApplication::translate("MainWindow", "Registrati", nullptr));
        registrationFirstPassword->setInputMask(QString());
        registrationFirstPassword->setText(QString());
        registrationFirstPassword->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        registrationUsername->setInputMask(QString());
        registrationUsername->setText(QString());
        registrationUsername->setPlaceholderText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        registrationButton->setText(QCoreApplication::translate("MainWindow", "Registrati", nullptr));
        registrationSecondPassword->setInputMask(QString());
        registrationSecondPassword->setText(QString());
        registrationSecondPassword->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ripeti password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

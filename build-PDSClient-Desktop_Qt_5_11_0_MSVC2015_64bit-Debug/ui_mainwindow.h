/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(800, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setStyleSheet(QLatin1String("QWidget{\n"
"background:#73c259;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        loginWidget_2 = new QWidget(centralwidget);
        loginWidget_2->setObjectName(QStringLiteral("loginWidget_2"));
        loginWidget_2->setFocusPolicy(Qt::ClickFocus);
        loginFrame = new QFrame(loginWidget_2);
        loginFrame->setObjectName(QStringLiteral("loginFrame"));
        loginFrame->setGeometry(QRect(50, 70, 281, 371));
        loginFrame->setStyleSheet(QLatin1String("QFrame{\n"
"	background: 	#ffffff;\n"
"	border-radius: 30px;\n"
"}"));
        loginFrame->setFrameShape(QFrame::StyledPanel);
        loginFrame->setFrameShadow(QFrame::Raised);
        loginLabel = new QLabel(loginFrame);
        loginLabel->setObjectName(QStringLiteral("loginLabel"));
        loginLabel->setGeometry(QRect(100, 20, 121, 41));
        loginLabel->setStyleSheet(QLatin1String("*{\n"
"font-familiy: Roboto;\n"
"font-size: 24px;\n"
"font:bold;\n"
"}"));
        loginUsername = new QLineEdit(loginFrame);
        loginUsername->setObjectName(QStringLiteral("loginUsername"));
        loginUsername->setGeometry(QRect(20, 120, 241, 31));
        loginUsername->setStyleSheet(QLatin1String("QLineEdit{\n"
"	background: transparent;\n"
"	border:none;\n"
"	color:#717072;\n"
"	border-bottom:1px solid #717072;\n"
"	font-family: Roboto;\n"
"}"));
        loginPassword = new QLineEdit(loginFrame);
        loginPassword->setObjectName(QStringLiteral("loginPassword"));
        loginPassword->setGeometry(QRect(20, 210, 241, 31));
        loginPassword->setStyleSheet(QLatin1String("QLineEdit{\n"
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
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(80, 300, 121, 51));
        loginButton->setStyleSheet(QLatin1String("\n"
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
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        registrationWidget = new QWidget(centralwidget);
        registrationWidget->setObjectName(QStringLiteral("registrationWidget"));
        registrationFrame = new QFrame(registrationWidget);
        registrationFrame->setObjectName(QStringLiteral("registrationFrame"));
        registrationFrame->setGeometry(QRect(40, 30, 301, 451));
        registrationFrame->setStyleSheet(QLatin1String("QFrame{\n"
"	background: 	#ffffff;\n"
"	border-radius: 30px;\n"
"}"));
        registrationFrame->setFrameShape(QFrame::StyledPanel);
        registrationFrame->setFrameShadow(QFrame::Raised);
        registrationNickname = new QLineEdit(registrationFrame);
        registrationNickname->setObjectName(QStringLiteral("registrationNickname"));
        registrationNickname->setGeometry(QRect(30, 170, 251, 31));
        registrationNickname->setStyleSheet(QLatin1String("QLineEdit{\n"
"	background: transparent;\n"
"	border:none;\n"
"	color:#717072;\n"
"	border-bottom:1px solid #717072;\n"
"	font-family: Roboto;\n"
"}"));
        registrationLabel = new QLabel(registrationFrame);
        registrationLabel->setObjectName(QStringLiteral("registrationLabel"));
        registrationLabel->setGeometry(QRect(100, 20, 121, 41));
        registrationLabel->setStyleSheet(QLatin1String("*{\n"
"font-familiy: Roboto;\n"
"font-size: 24px;\n"
"font:bold;\n"
"}"));
        registrationFirstPassword = new QLineEdit(registrationFrame);
        registrationFirstPassword->setObjectName(QStringLiteral("registrationFirstPassword"));
        registrationFirstPassword->setGeometry(QRect(30, 240, 251, 31));
        registrationFirstPassword->setStyleSheet(QLatin1String("QLineEdit{\n"
"	background: transparent;\n"
"	border:none;\n"
"	color:#717072;\n"
"	border-bottom:1px solid #717072;\n"
"	font-family: Roboto;\n"
"}"));
        registrationFirstPassword->setMaxLength(32767);
        registrationFirstPassword->setEchoMode(QLineEdit::Password);
        registrationUsername = new QLineEdit(registrationFrame);
        registrationUsername->setObjectName(QStringLiteral("registrationUsername"));
        registrationUsername->setGeometry(QRect(30, 100, 251, 31));
        registrationUsername->setStyleSheet(QLatin1String("QLineEdit{\n"
"	background: transparent;\n"
"	border:none;\n"
"	color:#717072;\n"
"	border-bottom:1px solid #717072;\n"
"	font-family: Roboto;\n"
"}"));
        registrationButton = new QPushButton(registrationFrame);
        registrationButton->setObjectName(QStringLiteral("registrationButton"));
        registrationButton->setGeometry(QRect(90, 380, 121, 51));
        registrationButton->setFocusPolicy(Qt::ClickFocus);
        registrationButton->setStyleSheet(QLatin1String("loginButton{ \n"
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
        registrationSecondPassword->setObjectName(QStringLiteral("registrationSecondPassword"));
        registrationSecondPassword->setGeometry(QRect(30, 310, 251, 31));
        registrationSecondPassword->setStyleSheet(QLatin1String("QLineEdit{\n"
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
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        loginLabel->setText(QApplication::translate("MainWindow", "Accedi", nullptr));
        loginUsername->setInputMask(QString());
        loginUsername->setText(QString());
        loginUsername->setPlaceholderText(QApplication::translate("MainWindow", "Username", nullptr));
        loginPassword->setInputMask(QString());
        loginPassword->setText(QString());
        loginPassword->setPlaceholderText(QApplication::translate("MainWindow", "Password", nullptr));
        loginButton->setText(QApplication::translate("MainWindow", "Accedi", nullptr));
        registrationNickname->setInputMask(QString());
        registrationNickname->setText(QString());
        registrationNickname->setPlaceholderText(QApplication::translate("MainWindow", "Nickname", nullptr));
        registrationLabel->setText(QApplication::translate("MainWindow", "Registrati", nullptr));
        registrationFirstPassword->setInputMask(QString());
        registrationFirstPassword->setText(QString());
        registrationFirstPassword->setPlaceholderText(QApplication::translate("MainWindow", "Password", nullptr));
        registrationUsername->setInputMask(QString());
        registrationUsername->setText(QString());
        registrationUsername->setPlaceholderText(QApplication::translate("MainWindow", "Username", nullptr));
        registrationButton->setText(QApplication::translate("MainWindow", "Registrati", nullptr));
        registrationSecondPassword->setInputMask(QString());
        registrationSecondPassword->setText(QString());
        registrationSecondPassword->setPlaceholderText(QApplication::translate("MainWindow", "Ripeti password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

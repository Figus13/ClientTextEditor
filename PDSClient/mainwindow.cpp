#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent, Client *client)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), client(client)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{

    QString username = ui->loginUsername->text();
    QString password = ui->loginPassword->text();
    client->login(username, password);
}

void MainWindow::onLoginSuccess(){
    FilesSelection fs;
    fs.show();//dove va sta roba??? boooh
}

void MainWindow::on_registrationButton_clicked()
{
    QString username = ui->registrationUsername->text();
    QString nick = ui->registrationNickname->text();
    QString password = ui->registrationFirstPassword->text();
    QString password2 = ui->registrationSecondPassword->text();

    if(password != password2){
       QMessageBox::information(this,"Registation","le password non coincidono");
    }else{
       client->registration(username,password,nick);
    }

}

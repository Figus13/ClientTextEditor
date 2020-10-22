#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    client = std::make_shared<Client>(new Client());
    QObject::connect(client.get(),  SIGNAL(login_successful()), this, SLOT(onLoginSuccess()));
    QObject::connect(client.get(),  SIGNAL(login_failed()), this, SLOT(onLoginFailed()));
    QObject::connect(client.get(),  SIGNAL(registration_successful()), this, SLOT(onRegistrationSuccess()));
    QObject::connect(client.get(),  SIGNAL(registration_failed()), this, SLOT(onRegistrationFailed()));
    QObject::connect(this,  SIGNAL(closing()), client.get(), SLOT(disconnectFromServer()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{

    QString username = ui->loginUsername->text();
    QString password = ui->loginPassword->text();
    if(username.isEmpty() || password.isEmpty()){
        QMessageBox::information(this,"Login","tutti i campi del form devono essere compilati");
        return;
    }
    client.get()->login(username, password);

}

void MainWindow::onLoginSuccess(){
    hide();
    FilesSelection *fs = new FilesSelection(nullptr, client);
    fs->show();
}

void MainWindow::onRegistrationSuccess(){
    hide();
    FilesSelection *fs = new FilesSelection(nullptr, client);
    fs->show();
}

void MainWindow::on_registrationButton_clicked()
{
    QString username = ui->registrationUsername->text();
    QString nick = ui->registrationNickname->text();
    QString password = ui->registrationFirstPassword->text();
    QString password2 = ui->registrationSecondPassword->text();

    if(password != password2){
       QMessageBox::information(this,"Registrazione","le password non coincidono");
       return;
    }
    if(password.isEmpty() || password2.isEmpty() || username.isEmpty() || nick.isEmpty()){
       QMessageBox::information(this,"Registrazione","tutti i campi del form devono essere compilati");
       return;
    }

    if(username.contains("/") || username.contains("\\") || username.contains(":") ||
       username.contains("*") || username.contains("?") || username.contains("\"") ||
       username.contains("<") || username.contains(">") || username.contains("|") || username.contains(" ")){
        QMessageBox::warning(this,"Registrazione","L'username non può contenere i seguenti caratteri: / \\ : * ? \" < > | 'spazio'");
        return;
    }

    client->registration(username,password,nick);
}

void MainWindow::onLoginFailed(){
    QMessageBox::information(this,"Login","Operazione di login non riuscita");
    ui->loginPassword->clear();
    return;
}

void MainWindow::onRegistrationFailed(int status){

    if(status == 2){
        QMessageBox::information(this,"Registrazione","Username già esistente!");
        ui->registrationFirstPassword->clear();
        ui->registrationSecondPassword->clear();
        ui->registrationNickname->clear();
        ui->registrationUsername->clear();
        return;
    }else if(status == 3){
        QMessageBox::information(this,"Registrazione","Nickname già esistente!");
        ui->registrationFirstPassword->clear();
        ui->registrationSecondPassword->clear();
        ui->registrationNickname->clear();
        return;
    }else{
        QMessageBox::information(this,"Registrazione","Operazione di registrazione non riuscita");
        ui->registrationFirstPassword->clear();
        ui->registrationSecondPassword->clear();
        ui->registrationNickname->clear();
        ui->registrationUsername->clear();
        return;

    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
   emit closing();
   event->accept();
}

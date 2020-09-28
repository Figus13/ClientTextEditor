#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    client = std::make_shared<Client>(Client());
    QObject::connect(client.get(),  SIGNAL(successful_login()), this, SLOT(onLoginSuccess()));
    QObject::connect(client.get(),  SIGNAL(login_refused()), this, SLOT(login_refused()));
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
    client->login(username, password);

}

void MainWindow::onLoginSuccess(){
    hide();
    //FilesSelection *fs = new FilesSelection(nullptr, client);
    std::unique_ptr<FilesSelection> fs = std::make_unique<FilesSelection>(nullptr, client);

    fs->show();
}

void MainWindow::on_registrationButton_clicked()
{
    QString username = ui->registrationUsername->text();
    QString nick = ui->registrationNickname->text();
    QString password = ui->registrationFirstPassword->text();
    QString password2 = ui->registrationSecondPassword->text();

    if(password != password2){
       QMessageBox::information(this,"Registation","le password non coincidono");
       return;
    }
    if(password.isEmpty() || password2.isEmpty() || username.isEmpty() || nick.isEmpty()){
       QMessageBox::information(this,"Registation","tutti i campi del form devono essere compilati");
       return;
    }

    client->registration(username,password,nick);
}

void MainWindow::login_refused(){
    QMessageBox::information(this,"Login","Operazione di login non è riuscita");
    return;
}

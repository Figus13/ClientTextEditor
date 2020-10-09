#include "showuridialog.h"
#include "ui_showuridialog.h"

ShowUriDialog::ShowUriDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowUriDialog)
{
    ui->setupUi(this);
}

void ShowUriDialog::setUri(QString uri) {
    ui->lineEdit->setText(uri);
}

ShowUriDialog::~ShowUriDialog()
{
    delete ui;
}

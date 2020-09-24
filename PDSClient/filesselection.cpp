#include "filesselection.h"
#include "ui_filesselection.h"

FilesSelection::FilesSelection(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FilesSelection)
{
    ui->setupUi(this);
}

FilesSelection::~FilesSelection()
{
    delete ui;
}

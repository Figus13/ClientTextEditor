#include "filesselection.h"
#include "ui_filesselection.h"

FilesSelection::FilesSelection(QWidget *parent, Client* client) :
    QMainWindow(parent),
    ui(new Ui::FilesSelection), client(client)
{
    ui->setupUi(this);
    client->getFiles(); //i file vengono gestiti nella slot onfilesListRefreshed
    connect(client, &Client::files_list_refreshed,
            this, &FilesSelection::onFilesListRefreshed);
    /*QVector<QString> files = client->getFiles();
    for(int i=0; i<files.size(); i++){
        ui->fileListWidget->addItem(files[i]);
    }*/
    QObject::connect(this,  SIGNAL(closing()), client, SLOT(disconnectFromServer()));

}

FilesSelection::~FilesSelection()
{
    delete ui;
}

void FilesSelection::onFilesListRefreshed(QVector<QString> files)
{
    for(int i=0; i<files.size(); i++){
        ui->fileListWidget->addItem(files[i]);
    }
}

void FilesSelection::on_newDocumentButton_clicked()
{
    NewFileDialog dialog;
    dialog.setModal(true);
    if(dialog.exec()){
        QString filename = dialog.getFilename();
        ui->fileListWidget->addItem(filename);

        TextEdit* mw = new TextEdit{0, client, filename};

        const QRect availableGeometry = mw->screen()->availableGeometry();
        mw->resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
        mw->move((availableGeometry.width() - mw->width()) / 2,
                   (availableGeometry.height() - mw->height()) / 2);
        hide();
        mw->show();
        QObject::connect(mw, &TextEdit::closeWindow, this, &FilesSelection::showWindow);
        client->getFile(filename);
    }
}

void FilesSelection::on_newFileFromLink_clicked()
{
    NewFileFromURIdialog dialog;
    dialog.setModal(true);
    if(dialog.exec()){
        QString filename = dialog.getFilename();
        ui->fileListWidget->addItem(filename);

        TextEdit* mw = new TextEdit{0, client, filename};

        const QRect availableGeometry = mw->screen()->availableGeometry();
        mw->resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
        mw->move((availableGeometry.width() - mw->width()) / 2,
                   (availableGeometry.height() - mw->height()) / 2);
        hide();
        mw->show();
        QObject::connect(mw, &TextEdit::closeWindow, this, &FilesSelection::showWindow);
        client->getFile(filename);
    }


}

void FilesSelection::on_fileListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString filename = item->text();
    client->getFile(filename);
    TextEdit* mw = new TextEdit{0, client, filename};
    hide();
    const QRect availableGeometry = mw->screen()->availableGeometry();
    mw->resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
    mw->move((availableGeometry.width() - mw->width()) / 2,
               (availableGeometry.height() - mw->height()) / 2);
    mw->show();
    QObject::connect(mw, &TextEdit::closeWindow, this, &FilesSelection::showWindow);
}

void FilesSelection::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    QString filename = item->text();
    client->getFile(filename);
    TextEdit* mw = new TextEdit{0, client, filename};
    hide();
    const QRect availableGeometry = mw->screen()->availableGeometry();
    mw->resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
    mw->move((availableGeometry.width() - mw->width()) / 2,
               (availableGeometry.height() - mw->height()) / 2);
    mw->show();
    QObject::connect(mw, &TextEdit::closeWindow, this, &FilesSelection::showWindow);
}

void FilesSelection::showWindow(){

    ui->fileListWidget->clear();
    client->getFiles();  //i file vengono gestiti nella slot onfilesListRefreshed
    /*QVector<QString> files = client->getFiles();
    for(int i=0; i<files.size(); i++){
        ui->fileListWidget->addItem(files[i]);
    }*/
    show();
}


void FilesSelection::closeEvent(QCloseEvent *e)
{
    client->getSocket()->disconnect();
    e->accept();
}


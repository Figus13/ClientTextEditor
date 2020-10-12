#include "filesselection.h"
#include "ui_filesselection.h"
#include <QMenu>
#include <QMessageBox>
#include "showuridialog.h"

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
    ui->fileListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->fileListWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(client, &Client::URI_Ready, this, &FilesSelection::onURIReady);
    connect(client, &Client::uri_error, this, &FilesSelection::onUriError);

}

FilesSelection::~FilesSelection()
{
    delete ui;
}

void FilesSelection::setUriRequest(bool status) {
    this->uriRequest = status;
}

void FilesSelection::onFilesListRefreshed(QVector<FileInfo *> files)
{
    ui->fileListWidget->clear();
    for(int i=0; i<files.size(); i++){   
        ui->fileListWidget->addItem(files[i]->getFileName() + " (" + files[i]->getNickname() + ")");
    }
}

void FilesSelection::on_newDocumentButton_clicked()
{
    NewFileDialog dialog;
    dialog.setModal(true);
    if(dialog.exec()){
        QString filename = dialog.getFilename();
        FileInfo * file = new FileInfo(filename,client->getUsername(),client->getNickname());
        ui->fileListWidget->addItem(filename + " ("+client->getNickname()+")");

        TextEdit* mw = new TextEdit{0, client, filename};

        const QRect availableGeometry = mw->screen()->availableGeometry();
        mw->resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
        mw->move((availableGeometry.width() - mw->width()) / 2,
                   (availableGeometry.height() - mw->height()) / 2);
        hide();
        mw->show();
        QObject::connect(mw, &TextEdit::closeWindow, this, &FilesSelection::showWindow);
        client->addFile(file);
    }
}

void FilesSelection::on_newFileFromLink_clicked()
{
    NewFileFromURIdialog dialog;
    dialog.setModal(true);
    if(dialog.exec()){
        QString uri = dialog.getUri();
        client->getFileFromURI(uri);
    }


}

void FilesSelection::on_fileListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString filename = item->text().split(" ")[0];
    int fileIndex = ui->fileListWidget->currentRow();
    client->getFile(fileIndex);
    TextEdit* mw = new TextEdit{0, client, filename};
    hide();
    const QRect availableGeometry = mw->screen()->availableGeometry();
    mw->resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
    mw->move((availableGeometry.width() - mw->width()) / 2,
               (availableGeometry.height() - mw->height()) / 2);
    mw->show();
    QObject::connect(mw, &TextEdit::closeWindow, this, &FilesSelection::showWindow);
}

void FilesSelection::showContextMenu(const QPoint &pos)
{
    // Handle global position
    QPoint globalPos = ui->fileListWidget->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu menu;

    /*
     * menu.addAction(tr("&Elimina file"), this, &FilesSelection::EraseFile); // DA IMPLEMENTARE
     */

    menu.addAction(tr("&Condividi Documento"), this, &FilesSelection::onShareURIButtonPressed);

    // Show context menu at handling position
    menu.exec(globalPos);
}

void FilesSelection::onShareURIButtonPressed(){
    setUriRequest(true);
    QString filename = ui->fileListWidget->item(ui->fileListWidget->currentRow())->text();
    client->requestURI(filename);
}

void FilesSelection::onURIReady(QString uri) {
    if(uriRequest) {
        setUriRequest(false);
        ShowUriDialog dialog;
        dialog.setUri(uri);
        dialog.setModal(true);
        if(dialog.exec()){}
    }
}

void FilesSelection::onUriError() {
    QMessageBox::information(this,"Condivisione documento","Condivisione non riuscita, URI inesistente.");
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


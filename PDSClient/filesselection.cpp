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
    connect(client, &Client::file_erased, this, &FilesSelection::onFileErased);
    connect(client, &Client::eraseFileError, this, &FilesSelection::onEraseFileError);

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

        int nameLength = files[i]->getFileName().size() - 4;

        /*
         * Eliminazione dell'estensione
         */

        ui->fileListWidget->addItem(files[i]->getFileName().remove(nameLength,4) + " (" + files[i]->getNickname() + ")");
    }
}

void FilesSelection::on_newDocumentButton_clicked()
{
    NewFileDialog dialog;
    dialog.setModal(true);
    if(dialog.exec()){
        QString filename = dialog.getFilename();


        if( filename.contains("/") || filename.contains("\\") || filename.contains(":") ||
                filename.contains("*") || filename.contains("?") || filename.contains("\"") ||
                filename.contains("<") || filename.contains(">") || filename.contains("|"))
        {
            QMessageBox::warning(this,"Nuovo Documento","Il nome del file non può contenere i seguenti caratteri: / \\ : * ? \" < > |");
            return;

        }else{
            bool flag = false;
            FileInfo * file = new FileInfo(filename + ".txt",client->getUsername(),client->getNickname());
            for(FileInfo * f : client->getMyFileList()){
                if( f->getFileName() == filename + ".txt" && f->getUsername() == client->getUsername()){
                  flag = true;
                  break;
                }
            }
            if(flag){
                QMessageBox::warning(this,"Nuovo Documento","Il file è già presente nella lista");
                return;
            }else{

                ui->fileListWidget->addItem(filename + " ("+client->getNickname()+")");
                int fileIndex =  ui->fileListWidget->count()-1;

                TextEdit* mw = new TextEdit{0, client, filename, fileIndex};

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
    TextEdit* mw = new TextEdit{0, client, filename, fileIndex};
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
    if(ui->fileListWidget->currentRow() != -1) {
        // Handle global position
        QPoint globalPos = ui->fileListWidget->mapToGlobal(pos);

        // Create menu and insert some actions
        QMenu menu;

        int fileIndex = ui->fileListWidget->currentRow();
        if(client->getMyFileList()[fileIndex]->getUsername() == client->getUsername()) {
            menu.addAction(tr("&Elimina file"), this, &FilesSelection::onEraseFileButtonPressed);
        }

        menu.addAction(tr("&Condividi Documento"), this, &FilesSelection::onShareURIButtonPressed);

        // Show context menu at handling position
        menu.exec(globalPos);
    }
}

void FilesSelection::onShareURIButtonPressed(){
    setUriRequest(true);
    int fileIndex = ui->fileListWidget->currentRow();
    client->requestURI(fileIndex);
}

void FilesSelection::onEraseFileButtonPressed() {
    int fileIndex = ui->fileListWidget->currentRow();
    client->eraseFile(fileIndex);
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

void FilesSelection::onFileErased(int index) {
    onFilesListRefreshed(client->getMyFileList());
}

void FilesSelection::onUriError() {
    QMessageBox::information(this,"Condivisione documento","Condivisione non riuscita, URI inesistente.");
}

void FilesSelection::onEraseFileError() {
    QMessageBox::information(this,"Elimina documento","Errore: impossibile eliminare il file.");
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


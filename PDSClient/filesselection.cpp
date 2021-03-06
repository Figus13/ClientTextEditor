#include "filesselection.h"
#include "ui_filesselection.h"
#include <QMenu>
#include <QMessageBox>
#include "showuridialog.h"
#include "changeprofiledialog.h"

FilesSelection::FilesSelection(QWidget *parent, Client* client) :
    QMainWindow(parent),
    ui(new Ui::FilesSelection), client(client)
{
    ui->setupUi(this);
    ui->nicknameLabel->setText(client->getNickname());
    ui->nicknameLabel->adjustSize();
    if(client->getHavePixmap()) {
        ui->profileImageLabel->setPixmap(client->getPixmap());
    }
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
    connect(client, &Client::erase_file_error, this, &FilesSelection::onEraseFileError);
    connect(client, &Client::nickname_error, this, &FilesSelection::onNicknameError);

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
                filename.contains("<") || filename.contains(">") || filename.contains("|") || filename.contains(" "))
        {
            QMessageBox::warning(this,"Nuovo Documento","Il nome del file non pu?? contenere i seguenti caratteri: / \\ : * ? \" < > | 'spazio'");
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
                QMessageBox::warning(this,"Nuovo Documento","Il file ?? gi?? presente nella lista");
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

void FilesSelection::on_changeProfileButton_clicked() {
    changeProfileDialog dialog;
    dialog.setModal(true);
    dialog.setNickname(client->getNickname());
    if(client->getHavePixmap()) {
        dialog.setPixmap(client->getPixmap());
    }
    if(dialog.exec()){
        QString nickname = dialog.getNickname();
        bool flag = false;
        if( nickname.contains("/") || nickname.contains("\\") || nickname.contains(":") ||
                nickname.contains("*") || nickname.contains("?") || nickname.contains("\"") ||
                nickname.contains("<") || nickname.contains(">") || nickname.contains("|") || nickname.contains(" "))
        {
            QMessageBox::warning(this,"Modifica profilo","Il nickname non pu?? contenere i seguenti caratteri: / \\ : * ? \" < > | 'spazio'");
            flag = true;
        }
        if(dialog.getHavePixmap()) {
            QPixmap image = dialog.getImagePixmap();      
            ui->profileImageLabel->setPixmap(image); 
            if(flag) {
                client->profileChanged(client->getNickname(), image);
            }
            else {
                client->profileChanged(nickname, image);
                ui->nicknameLabel->setText(nickname);
                ui->nicknameLabel->adjustSize();
            }
        }
        else {
            if(flag) {
                client->profileChanged(client->getNickname());
            }
            else{
                client->profileChanged(nickname);
                ui->nicknameLabel->setText(nickname);
                ui->nicknameLabel->adjustSize();
            }
        }
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

void FilesSelection::onUriError(int operation) {
    if(operation == 3) {
        QMessageBox::information(this,"Condivisione documento","Condivisione non riuscita, URI inesistente.");
    }
    else if(operation == 4) {
        QMessageBox::information(this,"Condivisione documento","Hai gi?? accesso al file.");
    }
}

void FilesSelection::onEraseFileError() {
    QMessageBox::information(this,"Elimina documento","Errore: impossibile eliminare il file.");
}

void FilesSelection::onNicknameError(QString oldNick) {
    ui->nicknameLabel->setText(oldNick);
    ui->nicknameLabel->adjustSize();
    QMessageBox::information(this,"Modifica profilo","Nickname gi?? esistente");
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


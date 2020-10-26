#include "filesselection.h"
#include "ui_filesselection.h"
#include <QMenu>
#include <QMessageBox>
#include "showuridialog.h"
#include "changeprofiledialog.h"

FilesSelection::FilesSelection(QWidget *parent, std::shared_ptr<Client> client) :
    QMainWindow(parent),
    ui(new Ui::FilesSelection), client(client)
{
    ui->setupUi(this);
    ui->nicknameLabel->setText(client.get()->getNickname());
    ui->nicknameLabel->adjustSize();
    if(client.get()->getHavePixmap()) {
        ui->profileImageLabel->setPixmap(client.get()->getPixmap());
    }
    client.get()->getFiles(); //i file vengono gestiti nella slot onfilesListRefreshed
    connect(client.get(), &Client::files_list_refreshed,
            this, &FilesSelection::onFilesListRefreshed);
    /*QVector<QString> files = client->getFiles();
    for(int i=0; i<files.size(); i++){
        ui->fileListWidget->addItem(files[i]);
    }*/
    QObject::connect(this,  SIGNAL(closing()), client.get(), SLOT(disconnectFromServer()));
    ui->fileListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->fileListWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(client.get(), &Client::URI_Ready, this, &FilesSelection::onURIReady);
    connect(client.get(), &Client::uri_error, this, &FilesSelection::onUriError);
    connect(client.get(), &Client::file_erased, this, &FilesSelection::onFileErased);
    connect(client.get(), &Client::erase_file_error, this, &FilesSelection::onEraseFileError);
    connect(client.get(), &Client::nickname_error, this, &FilesSelection::onNicknameError);

}

FilesSelection::~FilesSelection()
{
    delete ui;
}

void FilesSelection::setUriRequest(bool status) {
    this->uriRequest = status;
}

void FilesSelection::onFilesListRefreshed(QVector<std::shared_ptr<FileInfo>> files)
{
    ui->fileListWidget->clear();
    for(int i=0; i<files.size(); i++){

        int nameLength = files[i]->getFileName().size() - 4;

        /*
         * Eliminazione dell'estensione
         */

        ui->fileListWidget->addItem(files[i].get()->getFileName().remove(nameLength,4) + " (" + files[i].get()->getNickname() + ")");
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
            QMessageBox::warning(this,"Nuovo Documento","Il nome del file non può contenere i seguenti caratteri: / \\ : * ? \" < > | 'spazio'");
            return;

        }else{
            bool flag = false;
            std::shared_ptr<FileInfo> file (new FileInfo(filename + ".txt",client.get()->getUsername(), client.get()->getNickname()));
            for(std::shared_ptr<FileInfo> f : client.get()->getMyFileList()){
                if( f.get()->getFileName() == filename + ".txt" && f.get()->getUsername() == client.get()->getUsername()){
                  flag = true;
                  break;
                }
            }
            if(flag){
                QMessageBox::warning(this,"Nuovo Documento","Il file è già presente nella lista");
                return;
            }else{

                ui->fileListWidget->addItem(filename + " ("+client.get()->getNickname()+")");
                int fileIndex =  ui->fileListWidget->count()-1;

                TextEdit* mw = new TextEdit{0, client, filename, fileIndex};

                const QRect availableGeometry = mw->screen()->availableGeometry();
                mw->resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
                mw->move((availableGeometry.width() - mw->width()) / 2,
                         (availableGeometry.height() - mw->height()) / 2);
                hide();
                mw->show();
                QObject::connect(mw, &TextEdit::closeWindow, this, &FilesSelection::showWindow);
                client.get()->addFile(file);
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
        client.get()->getFileFromURI(uri);
    }
}

void FilesSelection::on_changeProfileButton_clicked() {
    changeProfileDialog dialog;
    dialog.setModal(true);
    dialog.setNickname(client.get()->getNickname());
    if(client.get()->getHavePixmap()) {
        dialog.setPixmap(client.get()->getPixmap());
    }
    if(dialog.exec()){
        QString nickname = dialog.getNickname();
        bool flag = false;
        if( nickname.contains("/") || nickname.contains("\\") || nickname.contains(":") ||
                nickname.contains("*") || nickname.contains("?") || nickname.contains("\"") ||
                nickname.contains("<") || nickname.contains(">") || nickname.contains("|") || nickname.contains(" "))
        {
            QMessageBox::warning(this,"Modifica profilo","Il nickname non può contenere i seguenti caratteri: / \\ : * ? \" < > | 'spazio'");
            flag = true;
        }
        if(dialog.getHavePixmap()) {
            QPixmap image = dialog.getImagePixmap();
            ui->profileImageLabel->setPixmap(image);
            if(flag) {
                client.get()->profileChanged(client.get()->getNickname(), image);
            }
            else {
                client.get()->profileChanged(nickname, image);
                ui->nicknameLabel->setText(nickname);
                ui->nicknameLabel->adjustSize();
            }
        }
        else {
            if(flag) {
                client.get()->profileChanged(client.get()->getNickname());
            }
            else{
                client.get()->profileChanged(nickname);
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
    client.get()->getFile(fileIndex);
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
        if(client.get()->getMyFileList()[fileIndex]->getUsername() == client.get()->getUsername()) {
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
    client.get()->requestURI(fileIndex);
}

void FilesSelection::onEraseFileButtonPressed() {
    int fileIndex = ui->fileListWidget->currentRow();
    client.get()->eraseFile(fileIndex);
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
    onFilesListRefreshed(client.get()->getMyFileList());
}

void FilesSelection::onUriError(int operation) {
    if(operation == 3) {
        QMessageBox::information(this,"Condivisione documento","Condivisione non riuscita, URI inesistente.");
    }
    else if(operation == 4) {
        QMessageBox::information(this,"Condivisione documento","Hai già accesso al file.");
    }
}

void FilesSelection::onEraseFileError() {
    QMessageBox::information(this,"Elimina documento","Errore: impossibile eliminare il file.");
}

void FilesSelection::onNicknameError(QString oldNick) {
    ui->nicknameLabel->setText(oldNick);
    ui->nicknameLabel->adjustSize();
    QMessageBox::information(this,"Modifica profilo","Nickname già esistente");
}

void FilesSelection::showWindow(){

    ui->fileListWidget->clear();
    client.get()->getFiles();  //i file vengono gestiti nella slot onfilesListRefreshed
    /*QVector<QString> files = client->getFiles();
    for(int i=0; i<files.size(); i++){
        ui->fileListWidget->addItem(files[i]);
    }*/
    show();
}


void FilesSelection::closeEvent(QCloseEvent *e)
{
    client.get()->getSocket()->disconnect();
    e->accept();
}


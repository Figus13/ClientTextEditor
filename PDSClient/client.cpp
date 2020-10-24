#include "client.h"

Client::Client(QObject* parent) : QObject(parent), counter(0)
{
    socket = new QTcpSocket(this);

    //quando si riceve il SIGNAL:connected viene chiamata la onConnection
    connect(socket, SIGNAL(connected()), this, SLOT(onConnected()));

    //quando si chiama close => disconnectedFromHost => SIGNAL:disconnected => onDisconnected
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    //connect(socket, &QAbstractSocket::disconnected, this, &Client::closed);
    //quando si chiama close => disconnectedFromHost => SIGNAL:disconnected => SIGNAL:closed = > chiusura applicazione
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(closed()));


    /*std::cout << "Inserire indirizzo server:\t";
    std::cin >> address;
    if (!std::cin.good()) {
        std::cout << "ERRORE indirizzo server" << std::endl;
        return;
    }
    std::cout << "Inserire porta server:\t";
    std::cin >> port;
    if (!std::cin.good()) {
        std::cout << "ERRORE porta server" << std::endl;
        return;
    }*/
    //address = "192.168.1.131";
    //port = 1500;
    //std::cout << "Dati inseriti:" << address << " " << port << std::endl;

    socket->connectToHost("127.0.0.1", 49002);//emette SIGNAL:connected
    //socket->connectToHost(QString::fromStdString(address), port);//emette SIGNAL:connected

    // we need to wait...
    if (!socket->waitForConnected(5000))
        qDebug() << "Error: " << socket->errorString();
    this->fileIndexOpened = -1; //ancora nessun file è stato aperto
}

void Client::onConnected(){
    if (socket->state() != QAbstractSocket::ConnectedState)	return;

    std::cout << "Connesso al server" << std::endl;

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

int Client::getSiteId(){
    return this->siteId;
}

void Client::onReadyRead(){
    while (socket->bytesAvailable() != 0) {
        QVector<int> position;
        int counter, recSiteId, alignment, textSize, insert;  //INSERT: 1 se inserimento, 0 se cancellazione
        QString color, font, text, nickname;
        QChar value;
        QVector<Symbol*> sVector;
        bool isBold, isItalic, isUnderlined;
        Symbol *s;
        QMap<int, QString> owners;
        if (socket->state() != QAbstractSocket::ConnectedState)	return;

        QDataStream in;
        in.setDevice(socket);//setto lo stream per la ricezione
        int operation;
        in >> operation;
        switch(operation){
        //ritorno login riuscito o fallito
        case 0:
            int status;
            in >> status;
            if(status == 0){
                login_failed();
            }else if(status == 1){
                int op;
                in >> op;
                if(op == 1) {
                    in >> this->username >> this->nickname;
                }
                else if(op == 2) {
                    QImage image;
                    in >> this->username >> this->nickname >> image;
                    this->image.convertFromImage(image);
                    haveImage = true;
                }
                /*int numFiles;
                in >> operation >> status;
                if(operation == 6 && status ==1){  //riceviamo i file.
                    in >>this->siteId >> numFiles;
                    files.clear();
                    for(int i=0; i<numFiles; i++){
                         QString filename;
                        in >> filename;
                        files.append(filename);
                    }
                    files_list_refreshed(files);
                    login_successful();
                }else{
                    qDebug() <<  "errore nella funzione per lettura file";*/
                login_successful();
            }
            break;
        case 1:
            std::cout<< "registration\n";
            int statusReg;
            in >> statusReg;
            if(statusReg!=1){
                registration_failed(statusReg);
            }else{
                in >> this->siteId >> this->username >> this->nickname;
                registration_successful();
            }
            break;
            
        case 3:
        {
            int siteIdSender=-1;
            //qDebug() << "3)Mandato dal server dopo l'inserimento o la cancellazione di un simbolo";
            int n_sym;
            QVector<Message> messages;
            in >> insert;
            if(insert==0){
                in >> siteIdSender;
            }
            if(insert==2){ //arrivo ack, richiesta blocco successivo
                QVector<Message> messages;
                onMessageReady(messages, fileIndexOpened);

                break;
            }
            in >> n_sym;
            for(int i=0; i<n_sym; i++){
                in >> recSiteId >> counter >> position >> value >>  isBold >> isItalic >> isUnderlined >> alignment >> textSize >> color >> font;
                s = new Symbol(position, counter, recSiteId, value, isBold, isItalic, isUnderlined, alignment, textSize, color, font);
                if(insert==1){ //nel caso sia un inserimento
                    if( recSiteId != this->siteId){ //il simbolo non l'ho aggiunto io.
                        Message m{'i', s};
                        messages.push_back(m);
                     //   message_from_server(m, siteIdSender); // ****FORSE QUI SAREBBE MEGLIO AGGIUNGERE IL FILENAME PER ESSERE SICURI DELL'INSERIMENTO*****
                    }
                }else{ //nel caso sia una cancellazione
                    Message m{'d', s};
                    messages.push_back(m);
                    //message_from_server(m, siteIdSender);
                }
            }
            messages_from_server(messages, siteIdSender);

            break;
        }
        case 4:
            // Ricezione dei metadati di un file già presente sul server.;
            int alreadyConnected;
            int siteId;
            int otherOwners;
            fileBuffer.clear();
            in >> alreadyConnected;
            for(int i = 0; i<alreadyConnected; i++){
                in >> siteId >> nickname;
                emit signal_connection(siteId, nickname, 1);
            }
            in >> otherOwners;
            for(int i=0; i<otherOwners; i++){
                in >> siteId >> nickname;
                owners.insert(siteId, nickname);
            }
            emit signal_owners(owners);
            break;

        case 6:
            int numFiles;
            in >> status;
            if(status == 1){  //riceviamo i file.
                in >>this->siteId >> numFiles;
                files.clear();
                for(int i=0; i<numFiles; i++){
                    QString filename;
                    QString usernameOwner; //riceve lo username del creatore
                    QString nicknameOwner;
                    in >> filename >> usernameOwner >> nicknameOwner;
                    FileInfo * file = new FileInfo(filename, usernameOwner, nicknameOwner);
                    files.append(file);
                }
                files_list_refreshed(files);
            }
            break;
        case 7:
            int operation;
            in >> operation;
            if(operation == 1){  //La condivisione è andata a buon fine, quindi aggiungo il nuovo file alla lista
                QString filename;
                QString usernameOwner; //riceve lo username del creatore
                QString nicknameOwner;
                in >> filename >> usernameOwner >> nicknameOwner;
                FileInfo * file = new FileInfo(filename, usernameOwner, nicknameOwner);
                files.append(file);
                files_list_refreshed(files);
            }  else if(operation == 2){
                QString uri;
                in >> uri;
                URI_Ready(uri);
            }
            else if (operation == 3 || operation == 4) {
                uri_error(operation);
            }
            break;
        case 8:
            int ins;
            in >> siteId >> nickname >> ins; //ins 0 rimuovi, 1 inserisci
            emit signal_connection(siteId, nickname, ins);
            break;
        case 9:
            in >> status;
            if(status == 1) { //cancellazione riuscita (lato server), eliminiamo e chiudiamo (se era aperto) il file
                QString filename;
                QString usernameOwner;
                in >> filename >> usernameOwner;
                for(FileInfo * f : files){
                    if( f->getFileName() == filename && f->getUsername() == usernameOwner){
                        int index = files.indexOf(f);
                        files.removeOne(f);
                        file_erased(index);
                        break;
                    }
                }
            }
            else {
                erase_file_error();
            }
            break;
        case 10:
        {
            QString oldNick;
            QString newNick;
            in >> oldNick >> newNick;
            for(FileInfo* file : files) {
                if(file->getNickname() == oldNick) {
                        file->setNickname(newNick);
                }
            }
            files_list_refreshed(files);
            refresh_text_edit(oldNick, newNick);
            break;
        }
        case 11:
        {
            int siteIdSender, cursorIndex;
            QString filepath;
            in >> filepath >> cursorIndex >> siteIdSender;
            if(filepath == this->files[this->fileIndexOpened]->getFilePath())
                remote_cursor_changed(cursorIndex, siteIdSender);
            break;
        }
        case 13:
        {
            int fileBlockSize;
            in >> fileBlockSize;
            for(int i = 0 ; i<fileBlockSize ; i++){
                in >> recSiteId  >> counter >> position  >> value >> isBold >> isItalic >> isUnderlined >> alignment >> textSize >> color >> font;
                s = new Symbol(position, counter, recSiteId, value, isBold, isItalic, isUnderlined, alignment, textSize,color, font);
                fileBuffer.push_back(s);
            }
            QByteArray buf;
            QDataStream out(&buf, QIODevice::WriteOnly);
            out << 13;
            socket->write(buf);
            socket->flush();
            break;
        }
        case 160:
        {
            qDebug() << "Fine comunicazione. Da ora scrivo il file sull'editor.";
            emit file_ready(this->fileBuffer);
            QByteArray buf;
            QDataStream out(&buf, QIODevice::WriteOnly);
            out << 13;
            socket->write(buf);
            socket->flush();
            break;
        }
        default: break;
        }
    }

}

void Client::closeFile(int fileIndex){
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    FileInfo * fi = files[fileIndex];
    out << 5 /*# operazione*/ << fi->getFileName() << fi->getUsername();
    socket->write(buf);
    socket->flush();
    fileIndexOpened = -1;
    files_list_refreshed(files);
    disconnect_URI();
}

Client::~Client(){

}

void Client::login(QString username, QString password){
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);

    out << 0 << username << password;

    socket->write(buf);
    socket->flush();
}

void Client::registration(QString username, QString password, QString nickName){

    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    out << 1 << username << password << nickName;

    socket->write(buf);
    socket->flush();
}

void Client::getFiles(){
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    out << 6;
    socket->write(buf);
    socket->flush();
    return; // i file vengono inviati dalla signal list_files_refreshed
}

QVector<FileInfo *> Client::getMyFileList(){
    return this->files;
}


/*
 * La addFile aggiunge alla lista di files un nuovo file e
 *  richiama la funzione per la ricezione di un file dal server
 */
void Client::addFile(FileInfo * file){
    files.append(file);
    int size = files.size() - 1;
    getFile(size);
}

void Client::setFileIndex(int index){
    fileIndexOpened = index;
}

void Client::eraseFile(int fileIndex) {
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    FileInfo * file = files[fileIndex];
    out << 9 << file->getFileName() << file->getUsername();
    socket->write(buf);
}

void Client::profileChanged(QString nickname, QPixmap image) {
    if(this->nickname != nickname || this->image != image) {       
        this->nickname = nickname;
        this->image = image;
        this->haveImage = true;
        QByteArray buf;
        QDataStream out(&buf, QIODevice::WriteOnly);
        QImage img = image.toImage();
        out << 10 << 1 << username << nickname << img;
        socket->write(buf);
    }
}

void Client::profileChanged(QString nickname) {
    if(this->nickname != nickname) {
        this->nickname = nickname;
        QByteArray buf;
        QDataStream out(&buf, QIODevice::WriteOnly);
        out << 10 << 2 << username << nickname;
        socket->write(buf);
    }
}

/*
 * modificata, ora riceve come argomento l'indice del file del vettore di files
 */
void Client::getFile(int fileIndex){

    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    FileInfo * file = files[fileIndex];
    out << 4 << file->getFileName() << file->getUsername() << siteId;
    fileIndexOpened = fileIndex;
    socket->write(buf);
}

void Client::disconnectFromServer(){
    //socket->close();
    socket->disconnectFromHost();
}

void Client::onMessageReady(QVector<Message> messages, int fileIndex){
    messagesReady.append(messages);
    if(messagesReady.size()==0){
        return;
    }

    FileInfo * fi = files[fileIndex];
    QByteArray buf_header;
    QDataStream out_header(&buf_header, QIODevice::WriteOnly);
    QByteArray buf_payload;
    QDataStream out_payload(&buf_payload, QIODevice::WriteOnly);
    QByteArray tot;
    int counter = 0;
    if(messagesReady[0].getAction()=='i'){
       while(!messagesReady.isEmpty()){
            if(messagesReady[0].getAction()!='i'){ //non stiamo ancora trattando inserimenti
                return;
            }
            counter++;
            Symbol *s = messagesReady[0].getSymbol();
            out_payload << s ->getSiteId() << s->getCounter() << s->getPosition() << s->getValue() << s->isBold()
                            << s->isItalic() << s->isUnderlined() << s->getAlignment() << s->getTextSize() << s->getColor() << s->getFont();
            if(buf_payload.size() > 50000){ //max buff 65532
                 out_header << 3 << 1 << fi->getFileName() << fi->getUsername() << counter;
                 tot.append(buf_header);
                 tot.append(buf_payload);
                 socket->write(tot);
                 socket->flush();
                 return;
            }
            messagesReady.remove(0);
       }
       out_header << 3 << 1 << fi->getFileName() << fi->getUsername() << counter;
       tot.append(buf_header);
       tot.append(buf_payload);
       socket->write(tot);
       socket->flush();
    }else{
        if(messages[0].getAction()=='d'){
            while(!messagesReady.isEmpty()){
                 if(messagesReady[0].getAction()!='d'){ //non stiamo ancora trattando cancellazioni
                     return;
                  }
                 counter++;
                 Symbol *s = messagesReady[0].getSymbol();
                 out_payload << s->getSiteId() << s->getCounter()  << s->getPosition();

                if(buf_payload.size() > 50000){ //max buff 65532
                    out_header << 3 << 0 << fi->getFileName() << fi->getUsername() << counter;
                    tot.append(buf_header);
                    tot.append(buf_payload);
                    socket->write(tot);
                    socket->flush();
                    return;
                }
                messagesReady.remove(0);
           }
           out_header << 3 << 0 << fi->getFileName() << fi->getUsername() << counter;
           tot.append(buf_header);
           tot.append(buf_payload);
           socket->write(tot);
           socket->flush();
        }
    }
}


QTcpSocket* Client::getSocket(){
    return socket;
}

void Client::requestURI(int fileIndex){
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);

    out << 7 << 2 << files[fileIndex]->getFileName() <<files[fileIndex]->getUsername();

    socket->write(buf);
    socket->flush();
}

void Client::onMyCursorPositionChanged(int index){
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);

    out << 11 << index;

    socket->write(buf);
    socket->flush();
}

void Client::getFileFromURI(QString uri) {
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    out << 7 << 1 << uri;

    socket->write(buf);
}

QString Client::getNickname(){
    return nickname;
}

QString Client::getUsername(){
    return username;
}

bool Client::getHavePixmap() {
    return haveImage;
}

QPixmap Client::getPixmap() {
    return image;
}

void Client::onSendAck(int fileIndex){
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    out << 12 << files[fileIndex]->getFileName() <<files[fileIndex]->getUsername();
    socket->write(buf);
    socket->flush();
}

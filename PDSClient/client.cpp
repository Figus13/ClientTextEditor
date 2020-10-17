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
        int counter, recSiteId, alignment, textSize, daButtare, insert;  //INSERT: 1 se inserimento, 0 se cancellazione
        QString color, font, text, nickname;
        QChar value;
        QVector<Symbol*> sVector;
        bool isBold, isItalic, isUnderlined;
        Symbol *s;

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
            if(statusReg==0){
                registration_failed();
            }else if(statusReg == 1){
                in >> this->siteId;
                registration_successful();
            }
            break;
        case 3:
            qDebug() << "3)Mandato dal server dopo l'inserimento o la cancellazione di un simbolo";
            int n_sym;
            in >> insert >> n_sym;
            for(int i=0; i<n_sym; i++){
                in >> recSiteId >> counter >> position >> value >>  isBold >> isItalic >> isUnderlined >> alignment >> textSize >> color >> font;
                s = new Symbol(position, counter, recSiteId, value, isBold, isItalic, isUnderlined, alignment, textSize, color, font);
                if(insert==1){ //nel caso sia un inserimento
                    if( recSiteId != this->siteId){ //il simbolo non l'ho aggiunto io.
                        Message m{'i', s};
                        message_from_server(m); // ****FORSE QUI SAREBBE MEGLIO AGGIUNGERE IL FILENAME PER ESSERE SICURI DELL'INSERIMENTO*****
                    }
                }else{ //nel caso sia una cancellazione
                    Message m{'d', s};
                    message_from_server(m);
                }
            }

            break;
        case 4:
            qDebug() << "4)Dobbiamo gestire la ricezione di un file già scritto.";
            int fileSize; //1 se inserimento, 0 se cancellazione
            int alreadyConnected;
            int siteId;
            in >> fileSize;
            for(int i = 0 ; i<fileSize ; i++){
                in  >>insert >> position >> counter >> recSiteId >> value >> isBold >> isItalic >> isUnderlined >> alignment >> textSize >> color >> font;
                s = new Symbol(position, counter, recSiteId, value, isBold, isItalic, isUnderlined, alignment, textSize,color, font);
                sVector.push_back(s);
            }
            if(fileSize!=0){
                file_ready(sVector);
            }
            in >> alreadyConnected;
            for(int i = 0; i<alreadyConnected; i++){
                in >> siteId >> nickname;
                emit signal_connection(siteId, nickname, 1); //PENSARCI: forse lo gestirei diversamente
            }
            break;
        case 6:
            int numFiles;
            in >> status;
            if(status == 1){  //riceviamo i file.
                in >>this->siteId >> numFiles;
                files.clear();
                for(int i=0; i<numFiles; i++){
                    QString filename;
                    in >> filename;
                    files.append(filename);
                }
                files_list_refreshed(files);
            }else{
                qDebug() <<  "errore nella funzione per lettura file";
            }
            break;
        case 7:
            int operation;
            in >> operation;
            if(operation == 1){  //riceviamo il file.

            }
            else if(operation == 2){
                QString uri;
                in >> uri;
                URI_Ready(uri);
            }
            break;
        case 8:
            int ins;
            in >> siteId >> nickname >> ins; //ins 0 rimuovi, 1 inserisci
            emit signal_connection(siteId, nickname, ins);
            break;
        case 11:
        {
            int siteIdSender, index;
            QString filename;
            in >> filename >> index >> siteIdSender;
            remote_cursor_changed(filename, index, siteIdSender);
        }
        default: break;
        }
    }

}

void Client::closeFile(QString filename){
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);

    out << 5 /*# operazione*/ << filename;
    socket->write(buf);
    socket->flush();
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

void Client::addFile(QString filename){
    files.append(filename);
}

void Client::getFile(QString filename){

    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    out << 4 << filename;

    socket->write(buf);
}

void Client::disconnectFromServer(){
    //socket->close();
    socket->disconnectFromHost();
}

void Client::onMessageReady(QVector<Message> messages, QString filename){
    QByteArray buf_header;
    QDataStream out_header(&buf_header, QIODevice::WriteOnly);
    QByteArray buf_payload;
    QDataStream out_payload(&buf_payload, QIODevice::WriteOnly);
    QByteArray tot;
    int counter = 0;
    if(messages[0].getAction()=='i'){

        for(int i=0; i< messages.size(); i++){
            counter++;
            Symbol *s = messages[i].getSymbol();
            out_payload << s ->getSiteId() << s->getCounter() << s->getPosition() << s->getValue() << s->isBold()
                        << s->isItalic() << s->isUnderlined() << s->getAlignment() << s->getTextSize() << s->getColor() << s->getFont();
            if(buf_payload.size() > 50000){ //max buff 65532
                out_header << 3 << 1 << filename << counter;
                counter=0;
                tot.append(buf_header);
                tot.append(buf_payload);
                socket->write(tot);
                socket->flush();
                out_payload.device()->reset();
                out_header.device()->reset();
                buf_header = "";
                buf_payload= "";
                tot = "";
            }

        }

    }else{
        if(messages[0].getAction()=='d'){
            for(int i=0; i< messages.size(); i++){
                counter++;
                Symbol *s = messages[i].getSymbol();
                out_payload << s->getSiteId() << s->getCounter()  << s->getPosition();

                if(buf_payload.size() > 50000){ //max buff 65532
                    out_header << 3 << 0 << filename << counter;
                    counter=0;
                    tot.append(buf_header);
                    tot.append(buf_payload);
                    socket->write(tot);
                    socket->flush();
                    out_payload.device()->reset();
                    out_header.device()->reset();
                    buf_header = "";
                    buf_payload= "";
                    tot = "";
                }
            }
        }
    }
    if(counter!=0){
        if(messages[0].getAction()=='i'){
            out_header << 3 << 1 << filename << counter;
        }else{
            out_header << 3 << 0 << filename << counter;
        }
        tot.append(buf_header);
        tot.append(buf_payload);
        socket->write(tot);
        socket->flush();
    }
}

/*void Client::onMessageReady(QVector<Message> messages, QString filename){
    int i=0;
    int counter=0;
    while(i<messages.size()){
        QByteArray buf_header;
        QDataStream out_header(&buf_header, QIODevice::WriteOnly);
        QByteArray buf_payload;
        QDataStream out_payload(&buf_payload, QIODevice::WriteOnly);
        QByteArray tot;

        if(messages[0].getAction()=='i'){

            for(; i< messages.size(); i++){
                counter++;
                Symbol *s = messages[i].getSymbol();
                out_payload << s ->getSiteId() << s->getCounter() << s->getPosition() << s->getValue() << s->isBold()
                            << s->isItalic() << s->isUnderlined() << s->getAlignment() << s->getTextSize() << s->getColor() << s->getFont();
                if(buf_payload.size() > 50000){ //max buff 65532
                    out_header << 3 << 1 << filename << counter;
                    counter=0;
                    tot.append(buf_header);
                    tot.append(buf_payload);
                    socket->write(tot);
                    socket->flush();
                    buf_header = "";
                    buf_payload= "";
                    tot = "";
                }

            }

        }else{
            if(messages[0].getAction()=='d'){
                for(; i< messages.size(); i++){
                    counter++;
                    Symbol *s = messages[i].getSymbol();
                    out_payload << s->getSiteId() << s->getCounter()  << s->getPosition();

                    if(buf_payload.size() > 50000){ //max buff 65532
                        out_header << 3 << 0 << filename << counter;
                        counter=0;
                        tot.append(buf_header);
                        tot.append(buf_payload);
                        socket->write(tot);
                        socket->flush();
                        buf_header = "";
                        buf_payload= "";
                        tot = "";
                    }
                }
            }
        }
    }
    if(counter!=0){
        if(messages[0].getAction()=='i'){
            out_header << 3 << 1 << filename << counter;
        }else{
            out_header << 3 << 0 << filename << counter;
        }
        tot.append(buf_header);
        tot.append(buf_payload);
        socket->write(tot);
        socket->flush();
    }
}*/

QTcpSocket* Client::getSocket(){
    return socket;
}

void Client::requestURI(QString filename){
    qDebug() << filename;
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);

    out << 7 << 2 << filename;

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

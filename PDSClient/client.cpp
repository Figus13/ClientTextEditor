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
    QVector<int> position;
    int counter, recSiteId, alignment, textSize, insert;  //INSERT: 1 se inserimento, 0 se cancellazione
    QString color, font;
    QChar value;
    bool isBold, isItalic, isUnderlined, isStyle;
    GenericSymbol *s;

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
            int numFiles;
            in >> this->siteId >> numFiles;
            for(int i=0; i<numFiles; i++){
                 QString filename;
                in >> filename;
                files.append(filename);
            }
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
        in >> insert >> isStyle >> position >> counter >> recSiteId;
        if(insert==1){ //nel caso sia un inserimento
            if (isStyle) {
                in >>  isBold >> isItalic >> isUnderlined >> alignment >> textSize >> color >> font;
                s = new StyleSymbol(isStyle, position, counter, recSiteId, isBold, isItalic, isUnderlined, alignment, textSize, color, font);
            }
            else {
                in >> value;
                s = new TextSymbol(isStyle, position, counter, recSiteId, value);
            }
            if( recSiteId != this->siteId){ //il simbolo non l'ho aggiunto io.
                Message m{'i', s};
                message_from_server(m); // ****FORSE QUI SAREBBE MEGLIO AGGIUNGERE IL FILENAME PER ESSERE SICURI DELL'INSERIMENTO*****
            }
        }else{ //nel caso sia una cancellazione
            if( recSiteId != this->siteId){ //il simbolo non l'ho rimosso io.
                //fare cancellazione in locale del simbolo ricevuto dal server
            }
        }
        break;
    case 4:
        qDebug() << "4)Dobbiamo gestire la ricezione di un file già scritto.";
        int fileSize; //1 se inserimento, 0 se cancellazione
        in >> fileSize;

        /**
         *  gestire i simboli ricevuti
         *
         *
         **/

        break;
    default: break;
    }
}

void Client::closeFile(QString filename){
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);

    out << 5 /*# operazione*/ << filename;

    socket->write(buf);
}

Client::~Client(){

}

void Client::login(QString username, QString password){
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);

    out << 0 << username << password;

    socket->write(buf);

}

void Client::registration(QString username, QString password, QString nickName){

    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    out << 1 << username << password << nickName;

    socket->write(buf);
}

QVector<QString> Client::getFiles(){
    return files;
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
    socket->close();
}

void Client::onMessageReady(Message mess, QString filename){
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    if(mess.getAction()=='i'){
        TextSymbol* ts = static_cast<TextSymbol*>(mess.getSymbol());
        //qDebug() << "Action " << mess.getAction() << "; Position " << ts->getPosition() << "; Value " << ts->getValue();
        out << 3 << 1 << filename << ts->getSiteId() << ts->getCounter() << ts->getPosition() << 0 << ts->getValue();
    }else{
        if(mess.getAction()=='d'){
            out << 3 << 0 << filename << mess.getSymbol()->getSiteId() << mess.getSymbol()->getCounter()
                << mess.getSymbol()->getPosition();
        }
    }
    socket->write(buf);
}


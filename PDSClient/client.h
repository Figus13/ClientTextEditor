#ifndef CLIENT_H
#define CLIENT_H
#include <QtNetwork>
#include <Symbol.h>
#include <iostream>
#include <message.h>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject* parent = 0);
    ~Client();
    void login(QString username, QString password);
    void registration(QString username, QString password, QString nick);
    void getFiles();
    void addFile(QString filename);
    void getFile(QString filename);
    void closeFile(QString filename);
    int getSiteId();
    QTcpSocket* getSocket();
    void requestURI(QString filename);

signals:
    void login_successful();
    void login_failed();
    void registration_successful();
    void registration_failed();
    void message_from_server(Message m);
    void files_list_refreshed(QVector<QString> files);
    void file_Ready(QVector<Symbol *> s, QString text);

public slots:
    void onMessageReady(Message m, QString filename);

private slots:
    void onConnected();
    void onReadyRead();

public slots:
    void disconnectFromServer();

private:
    QTcpSocket* socket;
    QString username;
    QString password;
    int siteId;
    int counter;
    QVector<QString> files;
    QVector<Symbol*> symbols;
    QMap<int, QString> clients;

};

#endif // CLIENT_H

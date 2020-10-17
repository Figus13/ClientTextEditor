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
    void file_ready(QVector<Symbol *> s);
    void URI_Ready(QString uri);
    void disconnect_URI();
    void signal_connection(int siteId, QString nickname, int ins);
    void signal_owners(QMap<int, QString> owners);
    void remote_cursor_changed(QString filename, int index, int siteIdSender);

public slots:
    void onMessageReady(QVector<Message> messages, QString filename);
    void onMyCursorPositionChanged(int index);

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
    QMap<int, QString> connectedUsers; //non usata per ora

};

#endif // CLIENT_H

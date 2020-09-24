#ifndef CLIENT_H
#define CLIENT_H
#include <QtNetwork>
#include <GenericSymbol.h>
#include <iostream>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject* parent = 0);
    ~Client();
    void login(QString username, QString password);
    void registration(QString username, QString password, QString nick);
private slots:
    void onConnect();
    void onReadyRead();
private:
    QTcpSocket* socket;
    QString username;
    QString password;
    int siteId;
    int counter;
    QVector<QString> files;
    QVector<GenericSymbol*> symbols;
    QMap<int, QString> clients;

};

#endif // CLIENT_H

#ifndef FILEINFO_H
#define FILEINFO_H
#include <QtNetwork>
#include <symbol.h>
#include <iostream>
#include <message.h>



class FileInfo: public QObject
{
    Q_OBJECT

public:
    FileInfo(QString filename, QString usernameOwner, QString nicknameOwner);
    QString getFileName();
    QString getUsername();
    QString getNickname();

private:
    QString filename;
    QString usernameOwner;
    QString nicknameOwner;

};

#endif // FILEINFO_H

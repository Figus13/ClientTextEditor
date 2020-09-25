#include "mainwindow.h"
#include "filesselection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client *client = new Client();
    MainWindow w(client);
    w.show();

    return a.exec();
}

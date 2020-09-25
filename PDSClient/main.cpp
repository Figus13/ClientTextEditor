#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  //std::shared_ptr<Client> client = std::make_shared<Client>(new Client{});
    //Client *client = new Client{};
    MainWindow w;


    w.show();
    return a.exec();
}

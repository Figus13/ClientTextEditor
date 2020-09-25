#ifndef FILESSELECTION_H
#define FILESSELECTION_H

#include <QMainWindow>
#include <client.h>
namespace Ui {
class FilesSelection;
}

class FilesSelection : public QMainWindow
{
    Q_OBJECT

public:
    explicit FilesSelection(QWidget *parent = nullptr, Client *client=nullptr);
    ~FilesSelection();

private:
    Ui::FilesSelection *ui;
    Client *client;
};

#endif // FILESSELECTION_H

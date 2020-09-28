#ifndef FILESSELECTION_H
#define FILESSELECTION_H

#include <QMainWindow>
#include <client.h>
#include <newfiledialog.h>

namespace Ui {
class FilesSelection;
}

class FilesSelection : public QMainWindow
{
    Q_OBJECT

public:
    explicit FilesSelection(QWidget *parent = nullptr, Client *client=nullptr);
    ~FilesSelection();

private slots:
    void on_newDocumentButton_clicked();
    void on_fileListWidget_clicked();

private:
    Ui::FilesSelection *ui;
    Client *client;
};

#endif // FILESSELECTION_H

#ifndef FILESSELECTION_H
#define FILESSELECTION_H

#include <QMainWindow>
#include <client.h>
#include <newfiledialog.h>
#include "texteditor/textedit.h"
#include <QListWidgetItem>

namespace Ui {
class FilesSelection;
}

class FilesSelection : public QMainWindow
{
    Q_OBJECT

public:
    explicit FilesSelection(QWidget *parent = nullptr, Client* client=nullptr);
    ~FilesSelection();

signals:
    void closing();

private slots:
    void on_newDocumentButton_clicked();
    void showWindow();
    void on_fileListWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::FilesSelection *ui;
    Client* client;
};

#endif // FILESSELECTION_H

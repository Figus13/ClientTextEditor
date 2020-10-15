#ifndef FILESSELECTION_H
#define FILESSELECTION_H

#include <QMainWindow>
#include <client.h>
#include <newfiledialog.h>
#include <newfilefromuridialog.h>
#include "texteditor/textedit.h"
#include <QListWidgetItem>
#include <QTableWidgetItem>

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

protected:
    void closeEvent(QCloseEvent *e) override;

private slots:
    void on_newDocumentButton_clicked();
    void on_newFileFromLink_clicked();
    void showWindow();
    void on_fileListWidget_itemDoubleClicked(QListWidgetItem *item);
    void onFilesListRefreshed(QVector<FileInfo *> files);
    void showContextMenu(const QPoint&);
    void onShareURIButtonPressed();
    void onEraseFileButtonPressed();
    void onURIReady(QString uri);
    void onUriError();
    void onFileErased(int index);
    void onEraseFileError();

private:
    Ui::FilesSelection *ui;
    Client* client;
    bool uriRequest = false;

    void setUriRequest(bool status);
};

#endif // FILESSELECTION_H

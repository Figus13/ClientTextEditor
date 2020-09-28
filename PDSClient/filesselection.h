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
    explicit FilesSelection(QWidget *parent = nullptr, std::shared_ptr<Client> client=nullptr);
    ~FilesSelection();

private slots:
    void on_newDocumentButton_clicked();

private:
    Ui::FilesSelection *ui;
    std::shared_ptr<Client> client;
};

#endif // FILESSELECTION_H

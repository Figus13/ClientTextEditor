#ifndef FILESSELECTION_H
#define FILESSELECTION_H

#include <QMainWindow>

namespace Ui {
class FilesSelection;
}

class FilesSelection : public QMainWindow
{
    Q_OBJECT

public:
    explicit FilesSelection(QWidget *parent = nullptr);
    ~FilesSelection();

private:
    Ui::FilesSelection *ui;
};

#endif // FILESSELECTION_H

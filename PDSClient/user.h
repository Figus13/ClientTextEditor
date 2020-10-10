#pragma once
#include <QLabel>
constexpr auto N_COLOR = 18;
class User
{
private:
    int id_color;//identificativo univoco del colore dell'utente
    QLabel *label;//label con il nome utente
    QLabel *label_cur;//label per il cursore semistrasparente
    QString username;
    int pos;//posizione del cursore dell'utente

public:
    User(int id_color, QString username, QWidget* text);
    QLabel* getLabel();
    QLabel* getLabel_cur();
    QColor getColor_qt();
    int getIdColor();
    int getPos();
    void setPos(int pos);
    QString getUsername();
    void setIdColor(int id_color);
    ~User();
};

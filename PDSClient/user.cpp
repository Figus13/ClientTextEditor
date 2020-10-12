#include "User.h"

std::vector<QString> colors = { "rgba(255,0,0,0.6)", "rgba(0,255,178,0.6)", "rgba(255,0,229,0.6)", "rgba(0,255,255,0.6)",
                                "rgba(0,25,255,0.6)", "rgba(0,255,26,0.6)", "rgba(255,0,77,0.6)", "rgba(204,255,0,0.6)",
                                "rgba(0,255,102,0.6)", "rgba(0,179,255,0.6)", "rgba(128,0,255,0.6)", "rgba(255,0,153,0.6)",
                                "rgba(255,153,0,0.6)", "rgba(127,255,0,0.6)", "rgba(255,77,0,0.6)", "rgba(0,102,255,0.6)",
                                "rgba(204,0,255,0.6)", "rgba(255,230,0,0.6)" };

QVector<QColor> colors_qt = {	QColor(255,0,0,153),QColor(0,255,178,153),QColor(255,0,229,153),QColor(0,255,255,153),
                                QColor(0,25,255,153),QColor(0,255,26,153),QColor(255,0,77,153),QColor(204,255,0,153),
                                QColor(0,255,102,153),QColor(0,179,255,153),QColor(128,0,255,153),QColor(255,0,153,153),
                                QColor(255,153,0,153),QColor(127,255,0,153),QColor(255,77,0,153),QColor(0,102,255,153),
                                QColor(204,0,255,153),QColor(255,230,0,153)};

/*
* Summary: Users::Users
            Costruttore della classe Users
* Parameters:	-int id_color: è l'id del colore dell'utente, è univoco;
                -Qstring username: è l'username dell'utente;
                -QWidget* text: contiene il testo della label;
* Return:		-l'oggetto;
*/
User::User(int id_color, QString username, QWidget* text)
{
    this->id_color = id_color;
    this->username = username;
    label = new QLabel(text);
    label_cur = new QLabel(text);
    label->hide();
    label_cur->hide();
    label->setTextFormat(Qt::RichText);
    label->setFixedHeight(20);
    label->setAutoFillBackground(false); //se settato a true si vede la label ma non quello sotto.
    label->setFont(QFont("Comic Sans MS", 9, 63, false));
    label->setStyleSheet("color:" + colors[id_color% N_COLOR]);
    label->setText("<p>" + username /*+ "  <img src=:/images/win/user.png vertical-align=middle> </p>"*/);
    label->topLevelWidget();
    label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    label->setWindowFlags(Qt::WindowStaysOnTopHint);
    label->setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    //label->setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    //label->raise();
    //labels[_siteId]->setAttribute(Qt::WA_AlwaysStackOnTop, true); TODO trovare un modo per metterla in primo piano

    label_cur->setTextFormat(Qt::RichText);
    label_cur->setStyleSheet("background-color: " + colors[id_color% N_COLOR]);
    label_cur->setFixedWidth(5);
    pos = 0;
}

QLabel* User::getLabel()
{
    return label;
}

QLabel* User::getLabel_cur()
{
    return label_cur;
}

QColor User::getColor_qt()
{
    return colors_qt[id_color];
}

int User::getIdColor()
{
    return id_color;
}

int User::getPos()
{
    return pos;
}

void User::setPos(int pos)
{
    this->pos = pos;
}

QString User::getUsername()
{
    return username;
}

void User::setIdColor(int id_color)
{
    this->id_color = id_color;
    label->setStyleSheet("color:" + colors[id_color]);
    label_cur->setStyleSheet("background-color: " + colors[id_color]);
}

User::~User()
{
}

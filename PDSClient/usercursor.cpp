#include "usercursor.h"

QVector<QColor> colors_qt = {	QColor(255,0,0,153),QColor(0,255,178,153),QColor(255,0,229,153),QColor(0,255,255,153),
                                QColor(0,25,255,153),QColor(0,255,26,153),QColor(255,0,77,153),QColor(204,255,0,153),
                                QColor(0,255,102,153),QColor(0,179,255,153),QColor(128,0,255,153),QColor(255,0,153,153),
                                QColor(255,153,0,153),QColor(127,255,0,153),QColor(255,77,0,153),QColor(0,102,255,153),
                                QColor(204,0,255,153),QColor(255,230,0,153)};
std::vector<QString> colors = { "rgba(255,0,0,0.6)", "rgba(0,255,178,0.6)", "rgba(255,0,229,0.6)", "rgba(0,255,255,0.6)",
                                "rgba(0,25,255,0.6)", "rgba(0,255,26,0.6)", "rgba(255,0,77,0.6)", "rgba(204,255,0,0.6)",
                                "rgba(0,255,102,0.6)", "rgba(0,179,255,0.6)", "rgba(128,0,255,0.6)", "rgba(255,0,153,0.6)",
                                "rgba(255,153,0,0.6)", "rgba(127,255,0,0.6)", "rgba(255,77,0,0.6)", "rgba(0,102,255,0.6)",
                                "rgba(204,0,255,0.6)", "rgba(255,230,0,0.6)" };

UserCursor::UserCursor(int siteId, QString nickname, int colorId, QWidget* text): User(siteId, nickname, colorId)
{
    //label = new QLabel(nickname);
    label = new QLabel(text);
    label->hide();
    label->setTextFormat(Qt::RichText);
    label->setFixedHeight(20);
    label->setAutoFillBackground(false);
    label->setFont(QFont("Comic Sans MS", 9, 63, false));
    label->setStyleSheet("color:" + colors[colorId% N_COLOR]);
    label->topLevelWidget();
    label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    label->setWindowFlags(Qt::WindowStaysOnTopHint);
    label->setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

    label_cur = new QLabel(text);
    label_cur->setTextFormat(Qt::RichText);
    label_cur->setStyleSheet("background-color: " + colors[colorId% N_COLOR]);
    label_cur->setFixedWidth(5);

    pos = 0;
}

QLabel* UserCursor::getLabel_cur()
{
    return label_cur;
}

void UserCursor::setLabelColor(int colorId){
    this->colorId = colorId;
    label->setStyleSheet("color:" + colors[colorId]);
    label_cur->setStyleSheet("background-color: " + colors[colorId]);
}

QLabel* UserCursor::getLabel(){
    return label;
}
int UserCursor::getPos(){
    return pos;
}

void UserCursor::setPos(int pos){
   this->pos = pos;
}

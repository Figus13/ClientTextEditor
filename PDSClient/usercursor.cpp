#include "usercursor.h"

QVector<QColor> qtColors = {	QColor(55, 55, 174,153),QColor(174, 55, 114,153),QColor(55, 174, 114,153),QColor(138, 55, 174,153),
                                QColor(55, 150, 174,153),QColor(174, 136, 55,153),QColor(217, 127, 42,153),QColor(91, 52, 16,153),
                                QColor(16, 54, 91,153),QColor(48, 237, 218,153),QColor(217, 91, 6,153),QColor(6, 27, 217,153),
                                QColor(165, 89, 89,153),QColor(165, 89, 165,153),QColor(121, 38, 180,153),QColor(21, 249, 245,153),
                                QColor(67, 196, 7,153),QColor(137, 173, 250,153)};
QVector<QString> colors = { "rgba(55, 55, 174,0.6)", "rgba(174, 55, 114,0.6)", "rgba(55, 174, 114,0.6)", "rgba(138, 55, 174,0.6)",
                                "rgba(55, 150, 174,0.6)", "rgba(174, 136, 55,0.6)", "rgba(217, 127, 42,0.6)", "rgba(91, 52, 16,0.6)",
                                "rgba(16, 54, 91,0.6)", "rgba(48, 237, 218,0.6)", "rgba(217, 91, 6,0.6)", "rgba(6, 27, 217,0.6)",
                                "rgba(165, 89, 89,0.6)", "rgba(165, 89, 165,0.6)", "rgba(121, 38, 180,0.6)", "rgba(21, 249, 245,0.6)",
                                "rgba(67, 196, 7,0.6)", "rgba(137, 173, 250,0.6)"};

UserCursor::UserCursor(int siteId, QString nickname, int colorId, QWidget* text): User(siteId, nickname, colorId)
{
    //label = new QLabel(nickname);
    /*label = new QLabel(text);
    label->hide();
    label->setTextFormat(Qt::RichText);
    label->setFixedHeight(20);
    label->setAutoFillBackground(false);
    label->setFont(QFont("Comic Sans MS", 9, 63, false));
    label->setStyleSheet("color:" + colors[colorId% N_COLOR]);
    label->topLevelWidget();
    label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    label->setWindowFlags(Qt::WindowStaysOnTopHint);
    label->setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);*/

    cursor = new QLabel(text);
    cursor->setTextFormat(Qt::RichText);
    cursor->setStyleSheet("background-color: " + colors[colorId% N_COLOR]);
    cursor->setFixedWidth(5);

    pos = 0;
}

QLabel* UserCursor::getCursor()
{
    return cursor;
}

void UserCursor::setLabelColor(int colorId){
    this->colorId = colorId;
    //label->setStyleSheet("color:" + colors[colorId]);
    cursor->setStyleSheet("background-color: " + colors[colorId]);
}

/*QLabel* UserCursor::getLabel(){
    return label;
}*/
int UserCursor::getPos(){
    return pos;
}

void UserCursor::setPos(int pos){
   this->pos = pos;
}

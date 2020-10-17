#include "user.h"
QVector<QColor> colors_qt1 = {	QColor(255,0,0,153),QColor(0,255,178,153),QColor(255,0,229,153),QColor(0,255,255,153),
                                QColor(0,25,255,153),QColor(0,255,26,153),QColor(255,0,77,153),QColor(204,255,0,153),
                                QColor(0,255,102,153),QColor(0,179,255,153),QColor(128,0,255,153),QColor(255,0,153,153),
                                QColor(255,153,0,153),QColor(127,255,0,153),QColor(255,77,0,153),QColor(0,102,255,153),
                                QColor(204,0,255,153),QColor(255,230,0,153)};
std::vector<QString> colors1 = { "rgba(255,0,0,0.6)", "rgba(0,255,178,0.6)", "rgba(255,0,229,0.6)", "rgba(0,255,255,0.6)",
                                "rgba(0,25,255,0.6)", "rgba(0,255,26,0.6)", "rgba(255,0,77,0.6)", "rgba(204,255,0,0.6)",
                                "rgba(0,255,102,0.6)", "rgba(0,179,255,0.6)", "rgba(128,0,255,0.6)", "rgba(255,0,153,0.6)",
                                "rgba(255,153,0,0.6)", "rgba(127,255,0,0.6)", "rgba(255,77,0,0.6)", "rgba(0,102,255,0.6)",
                                "rgba(204,0,255,0.6)", "rgba(255,230,0,0.6)" };

User::User(int siteId, QString nickname, int colorId):  nickname(nickname), siteId(siteId), colorId(colorId)
{
    color = colors_qt1[colorId%N_COLOR];
}
int User::getSiteId(){
    return siteId;
}
void User::setNickname(QString nickname){
    this->nickname = nickname;
}
QString User::getNickname(){
    return nickname;
}
QColor User::getColor(){
    return color;
}

int User::getColorId(){
    return colorId;
}

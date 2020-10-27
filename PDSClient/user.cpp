#include "user.h"
QVector<QColor> qtColors1 = {	QColor(55, 55, 174,153),QColor(174, 55, 114,153),QColor(55, 174, 114,153),QColor(138, 55, 174,153),
                                QColor(55, 150, 174,153),QColor(174, 136, 55,153),QColor(217, 127, 42,153),QColor(91, 52, 16,153),
                                QColor(16, 54, 91,153),QColor(48, 237, 218,153),QColor(217, 91, 6,153),QColor(6, 27, 217,153),
                                QColor(165, 89, 89,153),QColor(165, 89, 165,153),QColor(121, 38, 180,153),QColor(21, 249, 245,153),
                                QColor(67, 196, 7,153),QColor(137, 173, 250,153)};
QVector<QString> colors1 = { "rgba(55, 55, 174,0.6)", "rgba(174, 55, 114,0.6)", "rgba(55, 174, 114,0.6)", "rgba(138, 55, 174,0.6)",
                                "rgba(55, 150, 174,0.6)", "rgba(174, 136, 55,0.6)", "rgba(217, 127, 42,0.6)", "rgba(91, 52, 16,0.6)",
                                "rgba(16, 54, 91,0.6)", "rgba(48, 237, 218,0.6)", "rgba(217, 91, 6,0.6)", "rgba(6, 27, 217,0.6)",
                                "rgba(165, 89, 89,0.6)", "rgba(165, 89, 165,0.6)", "rgba(121, 38, 180,0.6)", "rgba(21, 249, 245,0.6)",
                                "rgba(67, 196, 7,0.6)", "rgba(137, 173, 250,0.6)"};

User::User(int siteId, QString nickname, int colorId):  nickname(nickname), siteId(siteId), colorId(colorId)
{
    color = qtColors1[colorId%N_COLOR];
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

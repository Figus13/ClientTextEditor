#ifndef USERCURSOR_H
#define USERCURSOR_H
#include <QtGui>
#include <QLabel>

constexpr auto N_COLOR = 18;
class UserCursor
{
public:
    UserCursor(int siteId, QString nickname, int colorId);
    int getColorId();
    void setNickname(QString nickname);
    QString getNickname();
    QColor getColor();
    void setColor(int colorId);
    QLabel* getLabel();
    int getPos();
    void setPos(int pos);
    int getSiteId();
private:
    QString nickname;
    int siteId;
    int pos;
    int colorId;
    QColor color;
    QLabel* label;
};

#endif // USERCURSOR_H

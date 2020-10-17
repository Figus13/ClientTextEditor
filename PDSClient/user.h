#ifndef USER_H
#define USER_H

#include <QtGui>

constexpr auto N_COLOR = 18;
class User
{
public:
    User(int siteId, QString nickname, int colorId);

    int getColorId();
    void setNickname(QString nickname);
    QString getNickname();
    QColor getColor();
    int getSiteId();
protected:
    QString nickname;
    int siteId;
    QColor color;
    int colorId;
};

#endif // USER_H

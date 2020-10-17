#ifndef USERCURSOR_H
#define USERCURSOR_H
#include <QtGui>
#include <QLabel>
#include "user.h"
class UserCursor: public User
{
public:
    UserCursor(int siteId, QString nickname, int colorId);
    UserCursor(User user);
    QLabel* getLabel();
    int getPos();
    void setPos(int pos);
    void setLabelColor(int colorId);
private:
    int pos;
    QLabel* label;
};

#endif // USERCURSOR_H

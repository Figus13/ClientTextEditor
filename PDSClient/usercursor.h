#ifndef USERCURSOR_H
#define USERCURSOR_H
#include <QtGui>
#include <QLabel>
#include "user.h"
class UserCursor: public User
{
public:
    UserCursor(int siteId, QString nickname, int colorId, QWidget* text);
    UserCursor(User user);
    QLabel* getLabel();
    int getPos();
    void setPos(int pos);
    void setLabelColor(int colorId);
    QLabel* getLabel_cur();
private:
    int pos;
    QLabel* label;
    QLabel *label_cur;
};

#endif // USERCURSOR_H

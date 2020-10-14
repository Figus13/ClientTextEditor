#ifndef USERCURSOR_H
#define USERCURSOR_H
#include <QtGui>
#include <QLabel>

constexpr auto N_COLOR = 18;
class UserCursor
{
public:
    UserCursor(int siteId, QString nickname, int colorId,  QWidget* text);
    int getColorId();
    void setNickname(QString nickname);
    QString getNickname();
    QColor getColor();
    void setColor(int colorId);
    QLabel* getLabel();
    int getPos();
    void setPos(int pos);
    int getSiteId();
    QLabel* getLabel_cur();

private:
    QString nickname;
    int siteId;
    int pos;
    int colorId;
    QColor color;
    QLabel* label;
    QLabel *label_cur;
};

#endif // USERCURSOR_H

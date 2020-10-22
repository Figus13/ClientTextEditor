#pragma once

#include <qvector.h>
#include <QtGui>

class Symbol
{
public:
    Symbol(QVector<int>& position, int counter, int siteId, QChar value, bool bold, bool italic, bool underlined, int alignment,
           int textSize, QColor color, QString font);
    Symbol();
    Symbol(const Symbol &s);
    virtual ~Symbol();
	QVector<int>& getPosition();
	void setPosition(QVector<int> position);
	int getCounter();
	int getSiteId();
    bool equals(std::shared_ptr<Symbol> s);
    QChar getValue();
    bool isBold();
    bool isItalic();
    bool isUnderlined();
    int getAlignment();
    int getTextSize();
    QColor& getColor();
    QString& getFont();
protected:
    QChar value;
	QVector<int> position;
	int counter;
	int siteId;
    bool bold;
    bool italic;
    bool underlined;
    int alignment;
    int textSize;
    QColor color;
    QString font;
};


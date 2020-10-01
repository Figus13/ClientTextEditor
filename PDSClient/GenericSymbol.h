#pragma once

#include <qvector.h>

class GenericSymbol
{
public:
	GenericSymbol(bool isStyle, QVector<int>& position, int counter, int siteId);
    GenericSymbol();
	virtual ~GenericSymbol();
	bool isStyle();
	QVector<int>& getPosition();
	void setPosition(QVector<int> position);
	int getCounter();
	int getSiteId();
	bool equals(GenericSymbol *gs);
protected:
	bool style;
	QVector<int> position;
	int counter;
	int siteId;
};


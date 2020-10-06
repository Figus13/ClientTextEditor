#pragma once
#include "Symbol.h"

class Message
{
private:

    char action;
    Symbol* s;

public:

    Message(const char action, Symbol* s);

    Message();

    ~Message();

    char getAction();

    void setAction(const char action);

    Symbol* getSymbol();

    void setSymbol(Symbol* s);
};

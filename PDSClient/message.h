#pragma once
#include "GenericSymbol.h"

class Message
{
private:

    char action;
    GenericSymbol* s;

public:

    Message(const char action, GenericSymbol* s);

    Message();

    ~Message();

    char getAction();

    void setAction(const char action);

    GenericSymbol* getSymbol();

    void setSymbol(GenericSymbol* s);
};

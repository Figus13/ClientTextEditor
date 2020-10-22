#pragma once
#include "symbol.h"

class Message
{
private:

    char action;
    std::shared_ptr<Symbol> s;

public:

    Message(const char action, std::shared_ptr<Symbol> s);

    Message();

    ~Message();

    char getAction();

    void setAction(const char action);

    std::shared_ptr<Symbol> getSymbol();

    void setSymbol(std::shared_ptr<Symbol> s);
};

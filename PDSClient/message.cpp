#include "message.h"

Message::Message(const char action, Symbol *s)
{
    this->action = action;
    this->s = s;
}

Message::Message()
{
}

Message::~Message()
{
}

char Message::getAction()
{
    return this->action;
}

Symbol* Message::getSymbol()
{
    return this->s;
}

void Message::setAction(const char action)
{
    this->action=action;
}

void Message::setSymbol(Symbol* s)
{
    this->s = s;
}

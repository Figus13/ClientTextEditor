#include "Message.h"

Message::Message(const char action, GenericSymbol *s)
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

GenericSymbol* Message::getSymbol()
{
    return this->s;
}

void Message::setAction(const char action)
{
    this->action=action;
}

void Message::setSymbol(GenericSymbol* s)
{
    this->s = s;
}

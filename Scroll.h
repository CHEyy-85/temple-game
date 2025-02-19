#ifndef SCROLL_H
#define SCROLL_H

#include "Object.h"

class Scroll: public Object
{
    public:
        Scroll(Temple* t, Actor* a, Coord p, std::string n);
        virtual std::string useFromInvent();
        virtual std::string getObjectType() const;
        virtual char getSymbol() const;
};

#endif
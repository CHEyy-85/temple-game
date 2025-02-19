#ifndef STAIRWAY_H
#define STAIRWAY_H

#include "Object.h"

class Stairway: public Object
{
    public:
        Stairway(Temple* t, Coord p);
        virtual std::string useFromInvent();
        virtual std::string getObjectType() const;
        virtual char getSymbol() const;
        virtual void getPicked();
};

#endif
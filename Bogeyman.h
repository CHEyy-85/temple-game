#ifndef BOGEYMAN_H
#define BOGEYMAN_H

#include "Monster.h"

class Bogeyman: public Monster
{
    public:
        Bogeyman(Temple* t, Coord p);
        virtual char getSymbol() const;
        virtual std::string getName() const;
        virtual void dropStuff();
        virtual void move();
};

#endif
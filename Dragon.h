#ifndef DRAGON_H
#define DRAGON_H

#include "Monster.h"

class Dragon: public Monster
{
    public:
        Dragon(Temple* t, Coord p);
        virtual void step();
        virtual char getSymbol() const;
        virtual std::string getName() const;
        virtual void dropStuff();
        virtual void move();
        
};

#endif
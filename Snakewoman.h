#ifndef SNAKEWOMAN_H
#define SNAKEWOMAN_H
#include"Monster.h"

class Snakewoman: public Monster
{
    public:
        Snakewoman(Temple* t, Coord p);
        virtual char getSymbol() const;
        virtual std::string getName() const;
        virtual void dropStuff();
        virtual void move();
};

#endif
#ifndef MONSTER_H
#define MONSTER_H

#include "Actor.h"
#include "utilities.h"
#include<string>

class Monster: public Actor
{
    public:
        Monster(Temple* t, Coord p, int hp, int maxHP, int a, int s, int d, int sleep);
        void step();
        virtual std::string getName() const = 0;
        virtual void dropStuff() = 0;
        virtual void move() = 0;
        virtual void dumpMove(int smellDistance);
};

#endif
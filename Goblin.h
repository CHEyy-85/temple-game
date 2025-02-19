#ifndef GOBLIN_H
#define GOBLIN_H

#include "Monster.h"
#include "Temple.h"

class Goblin: public Monster
{
    public:
        Goblin(Temple* t, Coord p, int smellDistance);
        virtual char getSymbol() const;
        virtual std::string getName() const;
        virtual void dropStuff();
        virtual void move();
        int optimalPath(char grid[][NUM_COL], Temple* t, Coord playerPos, Coord currentPos, int currentDepth, Coord& optimalNextPos);
    
    private:
        int m_smellDistance;
};

#endif
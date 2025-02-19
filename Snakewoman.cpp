#include "Snakewoman.h"
#include "Temple.h"
#include <iostream>

Snakewoman::Snakewoman(Temple* t, Coord p)
: Monster(t, p, randInt(3, 6), 0, 3, 2, 3, 0)
{
    setMaxHP(getHitPoint());
}

char Snakewoman::getSymbol() const
{
    return 'S';
}

std::string Snakewoman::getName() const
{
    return "the Snakewoman ";
}

void Snakewoman::dropStuff()
{
    if (trueWithProbability(1.0/3.0))
        getTemple() -> deadMonsterDrop(getPos(), "weapon", "magic fang of sleep");
}

void Snakewoman::move()
{
    dumpMove(3);
}
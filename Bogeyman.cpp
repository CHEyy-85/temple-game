#include "Bogeyman.h"
#include "Temple.h"
#include <iostream>

Bogeyman::Bogeyman(Temple* t, Coord p)
: Monster(t, p, randInt(5, 10), 0, 2, randInt(2, 3), randInt(2, 3), 0)
{
    setMaxHP(getHitPoint());
}

char Bogeyman::getSymbol() const
{
    return 'B';
}

std::string Bogeyman::getName() const
{
    return "the Bogeyman ";
}

void Bogeyman::dropStuff()
{
    if (trueWithProbability(0.1))
        getTemple() -> deadMonsterDrop(getPos(), "weapon", "magic axe");
}

void Bogeyman::move()
{
    dumpMove(5);
}
#include "Dragon.h"
#include "Temple.h"

Dragon::Dragon(Temple* t, Coord p)
: Monster(t, p, randInt(20, 25), 0, 4, 4, 4, 0)
{
    setMaxHP(getHitPoint());
}

void Dragon::step()
{
    return;
}

char Dragon::getSymbol() const
{
    return 'D';
}

std::string Dragon::getName() const
{
    return "the Dragon ";
}

void Dragon::dropStuff()
{
    std::string scrollsType[5] = {"teleportation", "enhance health", "strength", "enhance dexterity", "enhance armor"};
    int randIndex = randInt(0, 4);
    getTemple()->deadMonsterDrop(getPos(), "scroll", scrollsType[randIndex]);
}

void Dragon::move()
{
    return;
    // Dragon cannot move
}

#include "Stairway.h"
#include "Temple.h"
using namespace std;

Stairway::Stairway(Temple* t, Coord p)
: Object(t, nullptr, p, "stairway") {}

std::string Stairway::useFromInvent()
{
    return ""; // no need for stairway
}

string Stairway::getObjectType() const
{
    return "stairway";
}

char Stairway::getSymbol() const
{
    return '>';
}

void Stairway::getPicked()
{
    Temple* t = getTemple();
    t->newLevel();
}
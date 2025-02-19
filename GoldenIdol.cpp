#include "GoldenIdol.h"
#include "Temple.h"
using namespace std;

GoldenIdol::GoldenIdol(Temple* t, Coord p)
: Object(t, nullptr, p, "Golden Idol") {}

string GoldenIdol::getObjectType() const
{
    return "Golden Idol";
}

char GoldenIdol::getSymbol() const
{
    return '&';
}

void GoldenIdol::getPicked()
{
    //TODO: implemented how the GoldenIdol would do if it is picked
    getTemple()->pickUPGI();
    return;
}

std::string GoldenIdol::useFromInvent()
{
    return ""; // no need for Golden Idol
}
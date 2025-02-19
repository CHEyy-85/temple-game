#include "Scroll.h"
#include "Object.h"
#include "Actor.h"
#include "Temple.h"
using namespace std;

Scroll::Scroll(Temple* t, Actor* a, Coord p, std::string n)
: Object(t, a, p, n) {}

std::string Scroll::useFromInvent()
{
    // TODO: given different name of scroll,
    // perform different effect on Actor
    // then remove itself from the inventory
    Actor* player = getUser();

    string message = "You read the scroll called scroll of ";
    string name = getName();
    message += name;
    message += '\n';

    if (name == "enhance health")
    {
        player->setMaxHP(player->getMaxHP() + randInt(3, 8));
        message += "You feel your heart beating stronger.";
    }
    else if (name == "strength")
    {   
        player->setStrength(player->getStrength() + randInt(1, 3));
        message += "Your muscles bulge.";
    }
    else if (name == "enhance dexterity")
    {
        player->setDexterity(player->getDexterity() + 1);
        message += "You feel like less of a klutz.";
    }
    else if (name == "enhance armor")
    {
        player->setArmor(player->getArmor() + randInt(3, 8));
        message += "Your armor glows blue.";
    }
    else
    {
        getTemple()->teleportPlayer();
        message += "You feel your body wrenched in space and time.";
    }
    return message;
}

std::string Scroll::getObjectType() const
{
    return "scroll";
}

char Scroll::getSymbol() const
{
    return '?';
}




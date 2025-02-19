#include "Weapon.h"
#include "Actor.h"
using namespace std;

Weapon::Weapon(Temple* t, Actor* a, Coord p, std::string n)
: Object(t, a, p, n)
{
    setWeaponAttributes();
}

std::string Weapon::getVerb() const 
{
    string name = getName();
    if (name == "short sword")
        return "slashes ";
    else if (name == "mace")
        return "swings ";
    else if (name == "long sword")
        return "swings ";
    else if (name == "magic axe")
        return "chops ";
    else
        return "strikes ";
}

int Weapon::getDexterityBonus() const 
{
    return m_dexterityBonus;
}

int Weapon::getDamageAmount() const 
{
    return m_damageAmount;
}

string Weapon::useFromInvent()
{
    //TODO: get the weapon from inventory
    Actor* player = getUser();
    string message = "You are wielding ";
    message += getName();
    player->setWeapon(this);
    return message;
}

string Weapon::getObjectType() const
{
    return "weapon";
}

char Weapon::getSymbol() const
{
    return ')';
}

void Weapon::setWeaponAttributes()
{
    string name = getName();
    if (name == "short sword")
    {
        m_dexterityBonus = 0;
        m_damageAmount = 2;
    }
    else if (name == "mace")
    {
        m_dexterityBonus = 0;
        m_damageAmount = 2;
    }
    else if (name == "long sword")
    {
        m_dexterityBonus = 2;
        m_damageAmount = 4;
    }
    else if (name == "magic axe")
    {
        m_dexterityBonus = 5;
        m_damageAmount = 5;
    }
    else
    {
        m_dexterityBonus = 3;
        m_damageAmount = 2;
    }
}
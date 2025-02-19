#ifndef WEAPON_H
#define WEAPON_H

#include "Object.h"

class Weapon: public Object
{
    public:
        Weapon(Temple* t, Actor* a, Coord p, std::string n);
        std::string getVerb() const;
        int getDexterityBonus() const;
        int getDamageAmount() const;
        virtual std::string useFromInvent();
        virtual std::string getObjectType() const;
        virtual char getSymbol() const;

    private:
        int m_dexterityBonus;
        int m_damageAmount;

        void setWeaponAttributes();
};

#endif
#ifndef ACTOR_H
#define ACTOR_H

#include "Coord.h"

class Weapon;

class Temple;

class Actor
{
    public:
        Actor(Temple* t, Coord p, int hp, int maxHP, int a, int s, int d, int sleep);
        virtual ~Actor();

        // accesors
        Coord getPos() const;
        bool dead() const;
        virtual char getSymbol() const = 0;
        int getHitPoint() const;
        int getArmor() const;
        int getStrength() const;
        int getDexterity() const;
        int getSleep() const;
        int getMaxHP() const;
        Weapon* getWeapon() const;
        Temple* getTemple() const;

        // mutator
        void setPos(Coord c);
        void setHitPoint(int hp);
        void setMaxHP(int max);
        void setArmor(int a);
        void setStrength(int s);
        void setDexterity(int d);
        void setSleep(int s);
        void setWeapon(Weapon* w);

    private:
        Temple* m_temple;
        Coord m_pos;
        int m_hitPoint;
        int m_maxHP;
        int m_armor;
        int m_strength;
        int m_dexterity;
        int m_sleep;
        Weapon* m_weapon; 
};

#endif
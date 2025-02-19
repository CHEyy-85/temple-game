#ifndef OBJECT_H
#define OBJECT_H

#include "Coord.h"
#include "utilities.h"
#include <string>

class Actor;

class Temple;

class Object
{
    public:
        Object(Temple* t, Actor* a, Coord p, std::string n);
        virtual ~Object();
        std::string getName() const;
        Temple* getTemple() const;
        Coord getPos() const;
        Actor* getUser() const;

        virtual std::string useFromInvent() = 0;
        virtual std::string getObjectType() const = 0;
        virtual char getSymbol() const = 0;
        virtual void getPicked();
    private:
        Temple* m_temple;
        Actor* m_user; // nullptr if it is pickable
        Coord m_pos; // (0,0) if it is being carried by Actors rather than pickable
        std::string m_name; // when scroll is read, weapon is wielded or used to attack
};

#endif
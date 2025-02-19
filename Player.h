#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "Actor.h"
#include "utilities.h"

class Object;

class Player: public Actor
{
    public:
        Player(Temple* t, Coord c);
        virtual char getSymbol() const;
        void step(char c);
        void addToInvent(Object* o);
    private:
        // m_inventory will be a subset of m_objects of Temple
        // m_inventory will store copies of pointer of the objects that the player has
        // Player class should neither dynamically allocate nor deallocate Objects
        // only have 25 spaces, implemented in the pick up function.
        std::vector<Object*> m_inventory; 

        // helper functions for different steps a Player can take
        void moveAndAttack(char c);
        void pickUP();
        void useObject(char command, char choice); // wield weapon or read scroll
        char checkInvent();
        void useStair();
        void cheat();
    
};
#endif
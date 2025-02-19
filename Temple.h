/*
the game grid will be determined at construction time

a function called generate grid that take in level as argument
*/

#ifndef TEMPLE_H
#define TEMPLE_H

#include <vector>
#include <string>
#include <algorithm>

#include "utilities.h"
#include "Coord.h"

class Actor;

class Player;

class Monster;

class Object;

const int NUM_COL = 70;
const int NUM_ROW = 18;

class Temple
{
    public:
        // Constructor & Destructor
        Temple(int goblinSmellDistance);
        ~Temple();

        // Accessor
        void displayGame();
        Player* getPlayer() const; 
        bool GIPicked() const;
        std::vector<Coord> getValidCoord();

        // Mutator
        void addActors();
        void addPlayer(std::vector<Coord>& validPos);
        void addMonster(std::vector<Coord>& validPos, std::string type); // # depends on m_level
        void addObject(); // weapon and scroll

        void movePlayer(char command); // player takes its turn
        void moveMonsters(); // each monster takes its turn
        
        void newGrid(); // randomly generated rectangles and corridors
        void newLevel(); // after using stair

        bool actorsAt(Coord c);

        bool isValidPos(Coord c);
        void playerAttack(Coord c);
        void playerUseStair(Coord c);
        void playerPickUP(Coord c);

        void teleportPlayer(); // used for nextLevel but not new game and scroll of teleportation
        void addMessages(std::string message);

        void pickUPGI();

        void deadMonsterDrop(Coord p, std::string objectType, std::string subType);

        bool monsterAttack(Monster* m);

        bool playerAround(Coord p);


    private:
        Player* m_player;
        std::vector<Monster*> m_monsters;
        std::vector<Object*> m_groundObjects;
        std::vector<Object*> m_objects;
        std::vector<std::string> m_messages; 
        std::vector<Coord> m_validCoords; // positions that are not wall
        int m_level; // from 0 to 4
        int m_goblinSmellDistance;
        bool m_GIPicked;

        // helper function
        void createRectangles(std::vector< std::vector<int> >& rectangles);
        void generateCorridors(std::vector< std::vector<int> >& rectangles);
        
        int whichRectangles(std::vector< std::vector<int> >& rectangles, Coord endPoint);

        void topCorridors(Coord& start, Coord& turnPoint, Coord& endPoint);
        void pushTop(Coord& start, Coord& turnPoint, Coord& endPoint);

        void bottomCorridors(Coord& start, Coord& turnPoint, Coord& endPoint);
        void pushBottom(Coord& start, Coord& turnPoint, Coord& endPoint);

        void leftCorridors(Coord& start, Coord& turnPoint, Coord& endPoint);
        void pushLeft(Coord& start, Coord& turnPoint, Coord& endPoint);
        
        void rightCorridors(Coord& start, Coord& turnPoint, Coord& endPoint);
        void pushRight(Coord& start, Coord& turnPoint, Coord& endPoint);

        bool groundObjectAt(Coord c);
};

#endif
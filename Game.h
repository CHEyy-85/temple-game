// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Temple.h"
#include "Game.h"
#include "utilities.h"
#include <iostream>

// You may add data members and other member functions to this class.

class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();
private:
    Temple* m_temple;

};

#endif // GAME_INCLUDED

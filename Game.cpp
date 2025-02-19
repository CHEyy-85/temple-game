// Game.cpp

#include "Game.h"
#include "utilities.h"
#include "Temple.h"
#include "Player.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
    m_temple = new Temple(goblinSmellDistance);
    m_temple->newLevel();
}

Game::~Game()
{
    delete m_temple;
}

void Game::play()
{
    // cout << "The game hasn't been implemented yet." << endl;
    // cout << "Press q to exit game." << endl;
    // while (getCharacter() != 'q')
    //     ;
    m_temple->displayGame();
    Player* p = m_temple->getPlayer();

    if (p == nullptr)
        return;
    
    bool exitThruQ = false;

    // player not dead && Golden Idol not picked up
    while(!p->dead() && !m_temple->GIPicked())
    {
        char command = getCharacter();
        if (command == 'q')
        {
            exitThruQ = true;
            break;
        }
        
        m_temple->movePlayer(command);
        m_temple->moveMonsters();
        m_temple->displayGame();
    }

    if (!exitThruQ)
    {
        cout << "Press q to exit game." << endl;
        char command = getCharacter();
        while (command != 'q')
            command = getCharacter();
    }

    cout << endl <<  "Saving session...\n...copying shared history...\n...saving history...truncating history files...\n...completed." << endl;
}





// You will presumably add to this project other .h/.cpp files for the various
// classes of objects you need to play the game:  player, monsters, weapons, 
// etc.  You might have a separate .h/.cpp pair for each class (e.g., Player.h,
// Bogeyman.h, etc.), or you might put the class declarations for all actors in
// Actor.h, all game objects in GameObject.h, etc.

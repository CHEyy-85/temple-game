#include "Player.h"
#include "Object.h"
#include "Temple.h"
#include <iostream>
using namespace std;

Player::Player(Temple* t, Coord p)
: Actor(t, p, 20, 20, 2, 2, 2, 0){}

char Player::getSymbol() const
{
    return '@';
}

void Player::step(char c)
{
    // BEFORE each command from the user 1/10 prob of +1 hit point
    if(trueWithProbability(0.1) && (getHitPoint() + 1 <= getMaxHP()))
        setHitPoint(getHitPoint() + 1);
    
    if (getSleep() != 0) // if it is sleeping dont do other things
    {
        setSleep(getSleep() - 1);
        return;
    }
    
    switch (c)
    {
        char choice;
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT:
        case ARROW_UP:
            moveAndAttack(c);
            break;
        case 'c':
            cheat();
            break;
        case 'g':
            pickUP();
            break;
        case '>':
            useStair();
            break;
        case 'w':
        case 'r':
            choice = checkInvent();
            useObject(c, choice);
            break;
        case 'i':
            checkInvent();
            break;
        // case 'q' handled in Game play() directly
    }
}

void Player::moveAndAttack(char c)
{
    Temple* temp = getTemple();
    Coord pos = getPos();
    Coord nextPos;
    switch (c)
    {
        case ARROW_LEFT:
            nextPos = Coord(pos.getRow(), pos.getCol() - 1); 
            break;
        case ARROW_RIGHT:
            nextPos = Coord(pos.getRow(), pos.getCol() + 1); 
            break;
        case ARROW_UP:
            nextPos = Coord(pos.getRow() - 1, pos.getCol());
            break;
        case ARROW_DOWN:
            nextPos = Coord(pos.getRow() + 1, pos.getCol());
            break;
            
    }
    if (!temp->actorsAt(nextPos) && temp->isValidPos(nextPos)) // move 
    {
        setPos(nextPos);
    }
    else if(temp->isValidPos(nextPos)) // unable to move and attack monster
    {
        temp->playerAttack(nextPos);
    } 
}

void Player::pickUP()
{
    if (m_inventory.size() == 25)
        return;

    Temple* temp = getTemple();
    Coord pos = getPos();
    temp->playerPickUP(pos);
}

void Player::useObject(char command, char choice)
{
    int ch = choice - 'a';
    if (ch >= m_inventory.size())
        return;

    string message;
    switch (command)
    {
        case 'w': // wielding a weapon
            if (m_inventory.at(ch)->getObjectType() != "weapon")
                return;
            message = m_inventory.at(ch)->useFromInvent();
            break;
        case 'r': // reading a scroll
            if (m_inventory.at(ch)->getObjectType() != "scroll")
                return;
            message = m_inventory.at(ch)->useFromInvent();
            // Dont deallocate to void double deletion
            // NOTE: it is not erased from m_objects, so it will get deallocated at the end of the game
            m_inventory.erase(m_inventory.begin() + ch);
            break;
    }
    getTemple()->addMessages(message);
}

char Player::checkInvent()
{
    clearScreen();
    cout << "Inventory: " << endl;
    for (int i = 0; i < m_inventory.size(); i++)
    {
        cout << " " << static_cast<char>('a' + i) << ". ";
        if (m_inventory.at(i)->getObjectType() == "weapon")
            cout << m_inventory.at(i)->getName() << endl;
        else
            cout << "A scroll called scroll of " <<  m_inventory.at(i)->getName() << endl;
    }
    // press any key to return for 'i'
    // or return the next command to choose 'w' or 'o'
    char nextCommand = getCharacter();
    return nextCommand;
}

void Player::useStair()
{
    Temple* temp = getTemple();
    Coord pos = getPos();
    temp->playerUseStair(pos);
    return;
}

void Player::cheat()
{
    setMaxHP(50);
    setHitPoint(50);
    setStrength(9);
}

void Player::addToInvent(Object* o)
{
    m_inventory.push_back(o);
}
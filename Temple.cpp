#include "Temple.h"
#include "Weapon.h"
#include "Player.h"
#include "Scroll.h"
#include "Monster.h"
#include "Stairway.h"
#include "GoldenIdol.h"
#include "Snakewoman.h"
#include "Dragon.h"
#include "Object.h"
#include "Goblin.h"
#include "Bogeyman.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Temple::Temple(int goblinSmellDistance)
: m_level(-1), m_goblinSmellDistance(goblinSmellDistance), m_GIPicked(false){}

Temple::~Temple()
{  
    delete m_player;

    for (int i = 0; i < m_objects.size(); i++)
        delete m_objects[i];

    for (int i = 0; i < m_monsters.size(); i++)
        delete m_monsters[i];
}

void Temple::displayGame()
{
    char grid[NUM_ROW][NUM_COL];
    for (int r = 0; r < NUM_ROW; r++)
        for (int c = 0; c < NUM_COL; c++)
            grid[r][c] = '#';
    
    for (int i = 0; i < m_validCoords.size(); i++)
    {
        Coord temp = m_validCoords.at(i);
        grid[temp.getRow()][temp.getCol()] = ' ';
    }

    // display objects
    for(auto& object: m_groundObjects)
    {
        if (object->getUser() == nullptr) // double check on the ground, not in inventory or being used by monster
        {
            Coord object_pos = object->getPos();
            grid[object_pos.getRow()][object_pos.getCol()] = object->getSymbol();
        }
    }

    // display player
    
    Coord player_pos = m_player->getPos();
    grid[player_pos.getRow()][player_pos.getCol()] = '@';


    // display monsters
    for (auto& monster: m_monsters)
    {
        Coord monster_pos = monster->getPos();
        grid[monster_pos.getRow()][monster_pos.getCol()] = monster->getSymbol();
    }

    // draw grid
    clearScreen();
    for (int r = 0; r < NUM_ROW; r++)
    {
        for (int c = 0; c < NUM_COL; c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << "Level: " << m_level << ", Hit points: " << m_player->getHitPoint() << ", Armor: " << m_player->getArmor()
         << ", Strength: " << m_player->getStrength() << ", Dexterity: " << m_player->getDexterity() << endl;
    cout << endl;

    // display messages and clear it after
    for(string message: m_messages)
        cout << message << endl;
    m_messages.clear();
}


Player* Temple::getPlayer() const
{
    return m_player;
}

void Temple::addPlayer(vector<Coord>& validPos)
{
    if (m_level == 0)
    {
        int index = randInt(0, validPos.size() - 1);
        Coord pos = validPos.at(index);
        validPos.erase(validPos.begin() + index);

        m_player = new Player(this, pos);

        // because of the way the game env is generater, the validPos may contain duplicate values
        while(actorsAt(pos))
        {
            int index = randInt(0, validPos.size() - 1);
            Coord pos = validPos.at(index);
            validPos.erase(validPos.begin() + index);
            m_player->setPos(pos);
        }

        Weapon* w = new Weapon(this, m_player, Coord(0,0), "short sword");
        m_player->setWeapon(w);
        m_player->addToInvent(w);
        m_objects.push_back(w);
    }
    else
        teleportPlayer();
}


void Temple::addMonster(vector<Coord>& validPos, string type)
{
    int index = randInt(0, validPos.size() - 1);
    Coord pos = validPos.at(index);
    
    // because of the way the game env is generater, the validPos may contain duplicate values
    while(actorsAt(pos))
    {
        validPos.erase(validPos.begin() + index);
        index = randInt(0, validPos.size() - 1);
        pos = validPos.at(index);
    }

    validPos.erase(validPos.begin() + index);

    Monster* m;
    Weapon* w;

    if (type == "bogeyman")
    {
        m = new Bogeyman(this, pos);
        w = new Weapon(this, m, Coord(0,0), "short sword");
    }
    else if (type == "snakewoman")
    {
        m = new Snakewoman(this, pos);
        w = new Weapon(this, m, Coord(0,0), "magic fang of sleep");
    }
    else if (type == "dragon")
    {
        m = new Dragon(this, pos);
        w = new Weapon(this, m, Coord(0,0), "long sword");
    }
    else
    {
        m = new Goblin(this, pos, m_goblinSmellDistance);
        w = new Weapon(this, m, Coord(0,0), "short sword");
    }
    

    m->setPos(pos);
    m->setWeapon(w);
    m_monsters.push_back(m);
    m_objects.push_back(w);
}

void Temple::addActors()
{
    vector<Coord> validCoordCopy = m_validCoords;

    int monsterNum = randInt(2, 5 * (m_level + 1) + 1);

    string monsterType[] = {"bogeyman", "snakewoman", "goblin", "dragon"};

    // add Player first! 
    // because need to check player position when add monsters
    addPlayer(validCoordCopy);

    for (int i = 0; i < monsterNum; i++)
    {
        string type = monsterType[randInt(0, 3)];
        while ((type == "dragon" && m_level < 3) || (type == "bogeyman" && m_level < 2)) // no dragon for level 3 or lower; no bogeyman for level 2 or lower
            type = monsterType[randInt(0, 3)];
        
        addMonster(validCoordCopy, type);
    }
}

void Temple::addObject()
{
    // adding random weapon or scroll
    vector<Coord> validCoordCopy = m_validCoords;
    int num = randInt(2, 3);
    string weapons[3] = {"short sword", "long sword", "mace"};
    string scrolls[4] = {"enhance health", "strength", "enhance dexterity", "enhance armor"};

    for (int i = 0; i < num; i ++)
    {

        int index = randInt(0, validCoordCopy.size() - 1);
        Coord pos = validCoordCopy.at(index);
    
        // because of the way the game env is generater, the validPos may contain duplicate values
        while(groundObjectAt(pos))
        {
            validCoordCopy.erase(validCoordCopy.begin() + index);
            index = randInt(0, validCoordCopy.size() - 1);
            pos = validCoordCopy.at(index);
        }

        validCoordCopy.erase(validCoordCopy.begin() + index); // avoid overlapping objects

        int WorS = randInt(0, 1); // 0 for weapon, 1 for scroll 
        if(WorS) // scroll
        {
            int whichScroll = randInt(0, 3);
            Scroll* s = new Scroll(this, nullptr, pos, scrolls[whichScroll]);
            m_objects.push_back(s);
            m_groundObjects.push_back(s);
        }
        else
        {
            int whichWeapon = randInt(0, 2);
            Weapon* w = new Weapon(this, nullptr, pos, weapons[whichWeapon]);
            m_objects.push_back(w);
            m_groundObjects.push_back(w);
        }
    }
    // adding stairway if on level 0 to 3 & adding golden idol if on level 4
    int posNum = randInt(0, validCoordCopy.size() - 1);
    Coord pos = validCoordCopy.at(posNum);
    validCoordCopy.erase(validCoordCopy.begin() + posNum);

    if (m_level != 4)
    {
        Stairway* st = new Stairway(this, pos);
        m_objects.push_back(st);
        m_groundObjects.push_back(st);
    }
    else
    {   
        GoldenIdol* gi = new GoldenIdol(this, pos);
        m_objects.push_back(gi);
        m_groundObjects.push_back(gi);
    }
}

void Temple::movePlayer(char command)
{
    m_player->step(command);
}

void Temple::moveMonsters()
{
    // if the monster's sleeping time != 0 dont move, sleep --
    for (int i = 0; i < m_monsters.size(); i++)
    {
        Monster* m = m_monsters.at(i);
        // if the monster is dead, delete it 
        if(m->dead())
        {
            m -> dropStuff();
            delete m_monsters.at(i);
            m_monsters.erase(m_monsters.begin() + i);
            i--;
        }
        // if the monster is put to sleep, skip this round
        else if (m->getSleep() > 0)
        {
            m->setSleep(m->getSleep() - 1);
            continue;
        }
        else
        {
            m->step();
        } 
    }
}


void Temple::newGrid()
{   
    m_validCoords.clear(); // clear the validCoordination from last time first

    vector< vector<int> > rectangles;
    // upperleft r, c, height, width
    createRectangles(rectangles);
    generateCorridors(rectangles);
}

void Temple::newLevel()
{
    m_level += 1;

    // whenever get to a new level, clear the objects that are not picked up
    for (int i = 0; i < m_objects.size(); i++) 
    {
        if(m_objects.at(i)->getUser() == nullptr)
        {
            delete m_objects.at(i);
            m_objects.erase(m_objects.begin() + i);
            i--;
        }
    }

    // clear the groundObjects vector
    m_groundObjects.clear(); 

    // whenever get to a new level, clear the monster from last level
    for (int i = 0; i < m_monsters.size(); i++)
    {
        delete m_monsters.at(i);
    }
    m_monsters.clear();

    // create new game env
    newGrid();



    // add objects
    addObject();
    // add player and monsters
    addActors();
}


void Temple::createRectangles(vector< vector<int> >& rectangles)
{
    for (int i = 0; i < 9 && rectangles.size() < 7; i ++) // 9 is a empirical value 
    {
        int new_height = randInt(3, 8), 
            new_width = randInt(8, 15),
            new_r = randInt(1, NUM_ROW - 1 - new_height), 
            new_c = randInt(1, NUM_COL - 1 - new_width); 

        bool overlap = false;
        for(const auto& rect: rectangles)
        {
            int r = rect[0], c = rect[1], height = rect[2], width = rect[3];
            if (!(r+height < new_r || new_r+new_height < r 
                || c+width < new_c || new_c+new_width < c)) // if overlap with existing rectangles
            {
                overlap = true;
                break;
            }
        }
        if (!overlap)
        {
            vector<int> newRectangle;
            newRectangle.push_back(new_r);
            newRectangle.push_back(new_c);
            newRectangle.push_back(new_height);
            newRectangle.push_back(new_width);
            rectangles.push_back(newRectangle);
            // rectangles.push_back({new_r, new_c, new_height, new_width});
        }
    }


    while (rectangles.size() < 3) // ensure there are at least 3 rooms
    {
        int new_height = randInt(3, 8), 
            new_width = randInt(8, 15),
            new_r = randInt(1, NUM_ROW - 1 - new_height), 
            new_c = randInt(1, NUM_COL - 1 - new_width); 

        bool overlap = false;
        for(const auto& rect: rectangles)
        {
            int r = rect[0], c = rect[1], height = rect[2], width = rect[3];
            if (!(r+height < new_r || new_r+new_height < r 
                || c+width < new_c || new_c+new_width < c)) // if overlap with existing rectangles
            {
                overlap = true;
                break;
            }
        }
        if (!overlap)
        {
            vector<int> newRectangle;
            newRectangle.push_back(new_r);
            newRectangle.push_back(new_c);
            newRectangle.push_back(new_height);
            newRectangle.push_back(new_width);
            rectangles.push_back(newRectangle);
            // rectangles.push_back({new_r, new_c, new_height, new_width});
        }
    }      

    for(auto& rect: rectangles)
    {
        for(int r = rect[0]; r < rect[0] + rect[2]; r++)
        {
            for (int c = rect[1]; c < rect[1] + rect[3]; c++)
                m_validCoords.push_back(Coord(r, c));
        }
    }
}

void Temple::generateCorridors(vector< vector<int> >& rectangles)
{
    int numRectangles = rectangles.size(); // set up a 2d matrix 
    vector<vector<int> > corridorMatrix(numRectangles, vector<int>(numRectangles, 0));
    for (int i = 0; i < numRectangles; ++i) {
        corridorMatrix[i][i] = 1;
    }

    vector<int> triedDirection(4);

    for (int i = 0; i < numRectangles; i++)
    {
        vector<int> rect = rectangles.at(i);
        Coord start, turnPoint, endPoint;

        int id_other;

        int side = randInt(1, 4); // 1, 2, 3, 4 -> top, bottom, left, right

        int sum = 0; // if all direction is tried for this rectangle, move on, it is already connected by other rectangle anyway 
        for (int num: triedDirection)
            sum += num;
        if (sum == 4)
        {
            triedDirection = vector<int>(4);
            continue; 
        }

        switch(side)
        {
            case 1: // top
                triedDirection[0] = 1;

                start.setRow(rect[0]);
                start.setCol(rect[1] + rect[3]/2);
                
                topCorridors(start, turnPoint, endPoint);

                id_other = whichRectangles(rectangles, endPoint); // get which rectangle it is trying to connect to
                
                if(turnPoint == Coord(0,0) // if current direction does not work, retry a random direction
                  || (id_other != -1 && corridorMatrix[i][id_other] == 1))  // if there is already a connection
                {
                    i--;
                    break;
                }
                pushTop(start, turnPoint, endPoint);
                triedDirection = vector<int>(4);;
                if (id_other != -1)
                {
                    corridorMatrix[i][id_other] = 1;
                    corridorMatrix[id_other][i] = 1;
                }

                break;    

            case 2: // bottom
                triedDirection[1] = 1;

                start.setRow(rect[0] + rect[2]);
                start.setCol(rect[1] + rect[3]/2);
                bottomCorridors(start, turnPoint, endPoint);

                id_other = whichRectangles(rectangles, endPoint); // get which rectangle it is trying to connect to
                
                if(turnPoint == Coord(0,0) // if current direction does not work, retry a random direction
                  || (id_other != -1 && corridorMatrix[i][id_other] == 1))  // if there is already a connection
                {
                    i--;
                    break;
                }
                pushBottom(start, turnPoint, endPoint);
                triedDirection = vector<int>(4);
                if (id_other != -1)
                {
                    corridorMatrix[i][id_other] = 1;
                    corridorMatrix[id_other][i] = 1;
                }
                break;
            
            case 3: // left
                triedDirection[2] = 1;
                start.setRow(rect[0] + rect[2]/2);
                start.setCol(rect[1]);
                leftCorridors(start, turnPoint, endPoint);

                id_other = whichRectangles(rectangles, endPoint); // get which rectangle it is trying to connect to
                
                if(turnPoint == Coord(0,0) // if current direction does not work, retry a random direction
                  || (id_other != -1 && corridorMatrix[i][id_other] == 1))  // if there is already a connection
                {
                    i--;
                    break;
                }
                pushLeft(start, turnPoint, endPoint);
                triedDirection = vector<int>(4);
                if (id_other != -1)
                {
                    corridorMatrix[i][id_other] = 1;
                    corridorMatrix[id_other][i] = 1;
                }
                break;

            case 4: // right
                triedDirection[3] = 1;
                start.setRow(rect[0] + rect[2]/ 2);
                start.setCol(rect[1] + rect[3]);
                rightCorridors(start, turnPoint, endPoint);
                id_other = whichRectangles(rectangles, endPoint); // get which rectangle it is trying to connect to
                
                if(turnPoint == Coord(0,0) // if current direction does not work, retry a random direction
                  || (id_other != -1 && corridorMatrix[i][id_other] == 1))  // if there is already a connection
                {
                    i--;
                    break;
                }
                pushRight(start, turnPoint, endPoint);
                triedDirection = vector<int>(4);
                if (id_other != -1)
                {
                    corridorMatrix[i][id_other] = 1;
                    corridorMatrix[id_other][i] = 1;
                }
                break;
        }
    }
}

void Temple::topCorridors(Coord& start, Coord& turnPoint, Coord& endPoint)
{
    for(vector<Coord>::iterator it = m_validCoords.begin(); it != m_validCoords.end(); it++)
    {
        if (it->getRow() < start.getRow() && it->getCol() == start.getCol()) // direct corridor
        {
            turnPoint.setCol(it->getCol());
            turnPoint.setRow(it->getRow());
            endPoint = turnPoint;
            break; // break the loop 
        }
        else if (it->getRow() < start.getRow() - 2) // need a turn
        {
            turnPoint.setCol(start.getCol());
            turnPoint.setRow(it->getRow());
            endPoint.setCol(it->getCol());
            endPoint.setRow(it->getRow());
            // don't break, in case a direct corridor can be found
        }
    }
}

void Temple::pushTop(Coord& start, Coord& turnPoint, Coord& endPoint)
{
    for (int r = start.getRow(); r > turnPoint.getRow(); r--) // push all point to turning point to validCoords
        m_validCoords.push_back(Coord(r, start.getCol()));

    if (endPoint.getCol() >= turnPoint.getCol()) // endPoint on the right of turnPoint
    {
        for (int c = turnPoint.getCol(); c <= endPoint.getCol(); c++)
            m_validCoords.push_back(Coord(turnPoint.getRow(), c));
    }
    else // endPoint on the left of turnPoint
    {
        for (int c = turnPoint.getCol(); c >= endPoint.getCol(); c--)
            m_validCoords.push_back(Coord(turnPoint.getRow(), c));
    }
}

void Temple::bottomCorridors(Coord& start, Coord& turnPoint, Coord& endPoint)
{
    for(vector<Coord>::iterator it = m_validCoords.begin(); it != m_validCoords.end(); it++)
    {
        if (it->getRow() > start.getRow() && it->getCol() == start.getCol()) // direct corridor
        {
            turnPoint.setCol(it->getCol());
            turnPoint.setRow(it->getRow());
            endPoint = turnPoint;
            break; // break the loop 
        }
        else if (it->getRow() > start.getRow() + 2) // need a turn
        {
            turnPoint.setCol(start.getCol());
            turnPoint.setRow(it->getRow());
            endPoint.setCol(it->getCol());
            endPoint.setRow(it->getRow());
            // don't break, in case a direct corridor can be found
        }
    }
}

void Temple::pushBottom(Coord& start, Coord& turnPoint, Coord& endPoint)
{
    for (int r = start.getRow(); r < turnPoint.getRow(); r++) // push all point to turning point to validCoords
        m_validCoords.push_back(Coord(r, start.getCol()));
    

    if (endPoint.getCol() >= turnPoint.getCol()) // endPoint on the right of turnPoint
    {
        for (int c = turnPoint.getCol(); c <= endPoint.getCol(); c++)
            m_validCoords.push_back(Coord(turnPoint.getRow(), c));
    }
    else // endPoint on the left of turnPoint
    {
        for (int c = turnPoint.getCol(); c >= endPoint.getCol(); c--)
            m_validCoords.push_back(Coord(turnPoint.getRow(), c));
    }
}


void Temple::leftCorridors(Coord& start, Coord& turnPoint, Coord& endPoint)
{
    for(vector<Coord>::iterator it = m_validCoords.begin(); it != m_validCoords.end(); it++)
    {
        
        if (it->getCol() < start.getCol() && it->getRow() == start.getRow()) // direct corridor
        {
            turnPoint.setCol(it->getCol());
            turnPoint.setRow(it->getRow());
            endPoint = turnPoint;
            break; // break the loop 
        }
        else if (it->getCol() < start.getCol() - 2) // need a turn
        {
            turnPoint.setCol(it->getCol());
            turnPoint.setRow(start.getRow());
            endPoint.setCol(it->getCol());
            endPoint.setRow(it->getRow());
            // don't break, in case a direct corridor can be found
        }
    }
}

void Temple::pushLeft(Coord& start, Coord& turnPoint, Coord& endPoint)
{
    for (int c = start.getCol(); c > turnPoint.getCol(); c--) // push all point to turning point to validCoords
        m_validCoords.push_back(Coord(start.getRow(), c));

    if (endPoint.getRow() >= turnPoint.getRow()) // endPoint on the bottom of turnPoint
    {
        for (int r = turnPoint.getRow(); r <= endPoint.getRow(); r++)
            m_validCoords.push_back(Coord(r, turnPoint.getCol()));
    }
    else // endPoint on the top of turnPoint
    {
        for (int r = turnPoint.getRow(); r >= endPoint.getRow(); r--)
            m_validCoords.push_back(Coord(r, turnPoint.getCol()));
    }
}


void Temple::rightCorridors(Coord& start, Coord& turnPoint, Coord& endPoint)
{
    for(vector<Coord>::iterator it = m_validCoords.begin(); it != m_validCoords.end(); it++)
    {
        
        if (it->getCol() > start.getCol() && it->getRow() == start.getRow()) // direct corridor
        {
            turnPoint.setCol(it->getCol());
            turnPoint.setRow(it->getRow());
            endPoint = turnPoint;
            break; // break the loop 
        }
        else if (it->getCol() > start.getCol() + 2) // need a turn
        {
            turnPoint.setCol(it->getCol());
            turnPoint.setRow(start.getRow());
            endPoint.setCol(it->getCol());
            endPoint.setRow(it->getRow());
            // don't break, in case a direct corridor can be found
        }
    }
}

void Temple::pushRight(Coord& start, Coord& turnPoint, Coord& endPoint)
{
    for (int c = start.getCol(); c < turnPoint.getCol(); c++) // push all point to turning point to validCoords
        m_validCoords.push_back(Coord(start.getRow(), c));

    if (endPoint.getRow() >= turnPoint.getRow()) // endPoint on the bottom of turnPoint
    {
        for (int r = turnPoint.getRow(); r <= endPoint.getRow(); r++)
            m_validCoords.push_back(Coord(r, turnPoint.getCol()));
    }
    else // endPoint on the top of turnPoint
    {
        for (int r = turnPoint.getRow(); r >= endPoint.getRow(); r--)
            m_validCoords.push_back(Coord(r, turnPoint.getCol()));
    }
}


int Temple::whichRectangles(vector< vector<int> >& rectangles, Coord endPoint)
{
    int end_r = endPoint.getRow(), end_c = endPoint.getCol();
    for(int i = 0; i < rectangles.size(); i++)
    {
        int r = rectangles[i][0], c = rectangles[i][1], height = rectangles[i][2], width = rectangles[i][3];
    
        if (end_r >= r && end_r <= r + height && end_c >= c && end_c <= c + width)
            return i;
    }
    return -1;
}

void Temple::teleportPlayer()
{
    Coord nextPos = m_validCoords.at(randInt(0, m_validCoords.size() - 1));
    while(actorsAt(nextPos))
        nextPos = m_validCoords.at(randInt(0, m_validCoords.size() - 1));
    
    m_player->setPos(nextPos);
}


bool Temple::actorsAt(Coord c)
{
    if (m_player->getPos() == c)
        return true;
    
    for (auto& monster: m_monsters)
        if (monster->getPos() == c)
            return true;
        
    return false;
}

bool Temple::isValidPos(Coord c)
{
    for (Coord coord: m_validCoords)
        if (c == coord)
            return true;
    
    return false;
}

void Temple::playerAttack(Coord c)
{
    for(Monster* m: m_monsters)
    {
        if (m->getPos() == c) // find the monster at position c
        {

            Weapon* w = m_player->getWeapon();
            int attackerPoints = m_player->getDexterity() + w->getDexterityBonus();
            int defenderPoints = m->getDexterity() + m->getArmor();

            string message = "Player ";
            message += w->getVerb();
            message += w->getName();
            message += " at ";
            message += m->getName();
            

            if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) // Hit
            {
                int damagePoints = randInt(0, m_player->getStrength() + w->getDamageAmount() - 1);
                m->setHitPoint(m->getHitPoint() - damagePoints);


                if (m->dead())
                {
                    message += "dealing a final blow.";
                    m_messages.push_back(message);
                    break;
                }

                message += "and hits";
                if (w->getName() == "magic fang of sleep" && trueWithProbability(0.2)) // if it is fang of sleep
                {
                    m->setSleep(max(m->getSleep(), randInt(2, 6)));
                    message += ", putting ";
                    message += m->getName();
                    message += "to sleep";
                }    
                message += ".";
            }
            else
                message += "and misses.";
            
            m_messages.push_back(message);
            break;
        }
    }
}


void Temple::playerUseStair(Coord c)
{
    for(Object* obj: m_groundObjects)
    {
        if (obj->getPos() == c && obj->getObjectType() == "stairway")
            newLevel();
    }
}

void Temple::playerPickUP(Coord c)
{
    for(int i = 0; i < m_groundObjects.size(); i++)
    {
        Object* obj = m_groundObjects.at(i);
        if (obj->getPos() == c && (obj->getObjectType() == "weapon" || obj->getObjectType() == "scroll" || obj->getObjectType() == "Golden Idol"))
        {
            string message = "You pick up ";
            obj->getPicked();
            if (obj->getObjectType() == "weapon")
                message += obj->getName();
            else if(obj->getObjectType() == "scroll")
            {
                message += "a scroll called scroll of ";
                message += obj->getName();
            }
            else
                message += "the golden idol\nCongratulations, you won!";

            m_messages.push_back(message);
            m_groundObjects.erase(m_groundObjects.begin() + i);
            break;
        }
    }
}

void Temple::addMessages(string message)
{
    m_messages.push_back(message);
}

bool Temple::GIPicked() const
{
    return m_GIPicked;
}

void Temple::pickUPGI()
{
    m_GIPicked = true;
}

void Temple::deadMonsterDrop(Coord p, string objectType, string subType)
{
    // if some object is alreay there, return
    for (Object* obj: m_groundObjects)
        if (obj->getPos() == p)
            return;
    
    Object* toAdd;

    if (objectType == "weapon")
        toAdd = new Weapon(this, nullptr, p, subType);
    
    else if (objectType == "scroll")
        toAdd = new Scroll(this, nullptr, p, subType);
    
    m_objects.push_back(toAdd);
    m_groundObjects.push_back(toAdd);
}

// attack has the highest priority
// if returns false -> check move -> if false do nothing
bool Temple::monsterAttack(Monster* m)
{
    if (!playerAround(m->getPos()))
        return false;

    Weapon* w = m->getWeapon();
    int attackerPoints = m->getDexterity() + w->getDexterityBonus();
    int defenderPoints = m_player->getDexterity() + m_player->getArmor();

    string message = m->getName();
    message += w->getVerb();
    message += w->getName();
    message += " at Player ";
    
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) // Hit
    {
        int damagePoints = randInt(0, m->getStrength() + w->getDamageAmount() - 1);
        m_player->setHitPoint(m_player->getHitPoint() - damagePoints);


        if (m_player->dead()) // if kill the player
        {
            message += "dealing a final blow.";
            m_messages.push_back(message);
            return true;
        }

        message += "and hits";
            if (w->getName() == "magic fang of sleep" && trueWithProbability(0.2)) // if it is fang of sleep
            {
                m_player->setSleep(max(m_player->getSleep(), randInt(2, 6)));
                message += ", putting Player to sleep";
            }    
            message += ".";
    }
    else
        message += "and misses.";
    
    m_messages.push_back(message);
    return true;
}


bool Temple::playerAround(Coord p)
{
    Coord c = m_player->getPos();
    int row = p.getRow();
    int col = p.getCol();
    if (c == Coord(row + 1, col) || 
        c == Coord(row - 1, col) || 
        c == Coord(row, col + 1) || 
        c == Coord(row, col - 1))
        return true;
    else
        return false;
}

vector<Coord> Temple::getValidCoord()
{
    return m_validCoords;
}



bool Temple::groundObjectAt(Coord c)
{
    for (const auto& obj: m_groundObjects)
        if (obj->getPos() == c)
            return true;
    return false;
}
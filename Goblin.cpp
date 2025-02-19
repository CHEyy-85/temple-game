#include "Goblin.h"
#include "Temple.h"
#include "Coord.h"
#include "Player.h"
#include <iostream>

Goblin::Goblin(Temple* t, Coord p, int smellDistance)
: Monster(t, p, randInt(15, 20), 0, 1, 3, 3, 0), m_smellDistance(smellDistance)
{
    setMaxHP(getHitPoint());
}


char Goblin::getSymbol() const
{
    return 'G';
}

std::string Goblin::getName() const
{
    return "the Goblin ";
}


void Goblin::dropStuff()
{
    if (trueWithProbability(1.0/3.0))
    {
        std::string weapon;
        if (trueWithProbability(0.5))
            weapon = "magic axe";
        else 
            weapon = "magic fang of sleep";

        getTemple()->deadMonsterDrop(getPos(), "weapon", weapon);
    }
}


void Goblin::move()
{
    Temple* t = getTemple();
    std::vector<Coord> validCoords = t->getValidCoord();
    Player* p = t->getPlayer();
    Coord pos = getPos();
    int rowDiff = abs(pos.getRow() - p->getPos().getRow());
    int colDiff = abs(pos.getCol() - p->getPos().getCol());
    // manhattan distance is the shortest distance possible
    // if it is bigger than the smellDistance, dont bother to do recursive calculation
    if (rowDiff + colDiff > m_smellDistance)
        return;

    char grid[NUM_ROW][NUM_COL];
    for (int r = 0; r < NUM_ROW; r++)
        for (int c = 0; c < NUM_COL; c++)
            grid[r][c] = '#';
    
    for (int i = 0; i < validCoords.size(); i++)
    {
        Coord temp = validCoords.at(i);
        grid[temp.getRow()][temp.getCol()] = ' ';
    } 

    Coord nextPos;
    if (optimalPath(grid, t, p->getPos(), getPos(), 1, nextPos) != -1)
    {
        setPos(nextPos);
    }
        
}

int Goblin::optimalPath(char grid[][NUM_COL], Temple* t, Coord playerPos, Coord currentPos, int currentDepth, Coord& optimalNextPos)
{
    if (currentDepth > m_smellDistance)
        return -1;

    if (t->playerAround(currentPos))
        return currentDepth;

    int minDistance = m_smellDistance + 1;
    Coord nextPos;

    // Directions: up, down, left, right
    std::vector<Coord> directions;
    directions.push_back(Coord(currentPos.getRow() - 1, currentPos.getCol()));
    directions.push_back(Coord(currentPos.getRow() + 1, currentPos.getCol()));
    directions.push_back(Coord(currentPos.getRow(), currentPos.getCol() + 1));
    directions.push_back(Coord(currentPos.getRow(), currentPos.getCol() - 1));

    // recursively checkout all neighbors
    for (const Coord& dir: directions)
    {
        if (grid[dir.getRow()][dir.getCol()] == ' ' && !t->actorsAt(dir))
        {
            grid[dir.getRow()][dir.getCol()] = '.'; // mark cell as visited
            int distance = optimalPath(grid, t, playerPos, dir, currentDepth + 1, optimalNextPos);
            grid[dir.getRow()][dir.getCol()] = ' '; // Unmark the cell
            if (distance != -1 && distance < minDistance) 
            {
                minDistance = distance;
                nextPos = dir;
            }
        }
    }

    if (minDistance != m_smellDistance + 1) // if a path is found
    {
        optimalNextPos = nextPos;
        return minDistance;
    } 
    else 
        return -1;
    
}
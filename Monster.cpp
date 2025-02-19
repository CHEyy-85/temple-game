#include "Monster.h"
#include "Player.h"
#include "Temple.h"
#include <cstdlib>
#include <iostream>

Monster::Monster(Temple* t, Coord p, int hp, int maxHP, int a, int s, int d, int sleep)
: Actor(t, p, hp, maxHP, a, s, d, sleep) {}


void Monster::step()
{
    Temple* t = getTemple();
    
    // try to attack first
    if (t->monsterAttack(this))
        return;

    // try to move
    move();
}


void Monster::dumpMove(int smellDistance)
{
    Temple* t = getTemple();
    Player* p = t->getPlayer();
    Coord pos = getPos();
    int rowDiff = pos.getRow() - p->getPos().getRow();
    int colDiff = pos.getCol() - p->getPos().getCol();
    if (abs(rowDiff) + abs(colDiff) <= smellDistance)
    {
        Coord nextPos;
        std::vector<int> allTried(4, 0);
        int attempt = 0;
        while(!t->isValidPos(nextPos) || t->actorsAt(nextPos))
        {
            if(attempt > 2)
                break;
            attempt ++;

            if(rowDiff > 0 && allTried.at(0) == 0)// move up is closer
            {
                nextPos = Coord(pos.getRow() - 1, pos.getCol());
                allTried.at(0) = 1;
            } 
            else if (rowDiff < 0 && allTried.at(1) == 0) // move down is closer
            {
                nextPos = Coord(pos.getRow() + 1, pos.getCol());
                allTried.at(1) = 1;
            }
            else if (colDiff > 0 && allTried.at(2) == 0) // move left is closer
            {
                nextPos = Coord(pos.getRow(), pos.getCol() - 1);
                allTried.at(2) = 1;
            }
            else if (colDiff < 0 && allTried.at(3) == 0) // move right is closer
            {
                nextPos = Coord(pos.getRow(), pos.getCol() + 1);
                allTried.at(3) = 1;
            }  
        }
        if (t->isValidPos(nextPos) && !t->actorsAt(nextPos))
            setPos(nextPos);
    }
}
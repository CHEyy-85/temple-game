#include "Object.h"
#include "Temple.h"
#include <iostream>
#include "Player.h"
using namespace std;

Object::Object(Temple* t, Actor* a, Coord p, std::string n)
: m_temple(t), m_user(a), m_pos(p), m_name(n){} 

Object::~Object(){}

std::string Object::getName() const
{
    return m_name;
}

Temple* Object::getTemple() const
{
    return m_temple;
}

Coord Object::getPos() const
{
    return m_pos;
}

Actor* Object::getUser() const
{
    return m_user;
}

void Object::getPicked()
{
    if(m_user == nullptr)
    {
        m_user = m_temple->getPlayer();
        m_pos = Coord(0, 0);
        m_temple->getPlayer()->addToInvent(this);
    }
    else
        cerr << "Picking Process Error";
}
#include "Actor.h"
using namespace std;

Actor::Actor(Temple* t, Coord p, int hp, int maxHP, int a, int s, int d, int sleep)
: m_temple(t), m_pos(p), m_hitPoint(hp), m_maxHP(maxHP), m_armor(a), m_strength(s), m_dexterity(d), m_sleep(sleep){}

Actor::~Actor(){}

Coord Actor::getPos() const
{
    return m_pos;
}

bool Actor::dead() const
{
    return m_hitPoint <= 0;
}

int Actor::getHitPoint() const
{
    return m_hitPoint;
}

int Actor::getMaxHP() const
{
    return m_maxHP;
}

int Actor::getArmor() const
{
    return m_armor;
}

int Actor::getStrength() const
{
    return m_strength;
}

int Actor::getDexterity() const {
    return m_dexterity;
}

int Actor::getSleep() const {
    return m_sleep;
}

Weapon* Actor::getWeapon() const {
    return m_weapon;
}

Temple* Actor::getTemple() const {
    return m_temple;
}

void Actor::setPos(Coord c) {
    m_pos = c;
}

void Actor::setHitPoint(int hp) {
    m_hitPoint = hp;
}

void Actor::setMaxHP(int max)
{
    m_maxHP = max;
}

void Actor::setArmor(int a) {
    m_armor = a;
}

void Actor::setStrength(int s) {
    m_strength = s;
}

void Actor::setDexterity(int d) {
    m_dexterity = d;
}

void Actor::setSleep(int s) {
    m_sleep = s;
}

void Actor::setWeapon(Weapon* w) {
    m_weapon = w;
}


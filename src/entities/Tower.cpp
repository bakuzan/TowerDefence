#include "Tower.h"

Tower::Tower(TowerType towerType)
    : type(towerType), level(1)
{
    // Constructor
}

Tower::~Tower()
{
    // Destructor
}

// Publics

const int Tower::getLevel() const
{
    return level;
}

const TowerType Tower::getType() const
{
    return type;
}

void Tower::levelUp()
{
    ++level;
}
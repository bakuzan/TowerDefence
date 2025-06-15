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

void Tower::render(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

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
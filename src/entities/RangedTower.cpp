#include "RangedTower.h"

RangedTower::RangedTower(TowerType towerType,
                         const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
                         sf::Vector2f position)
    : Tower(towerType, texture, textureRects, position)
{
    // Constructor
}

RangedTower::~RangedTower()
{
    // Destructor
}

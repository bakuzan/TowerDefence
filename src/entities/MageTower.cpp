#include "constants/Constants.h"
#include "MageTower.h"

MageTower::MageTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
                     sf::Vector2f position)
    : RangedTower(TowerType::MAGE, texture, textureRects, position)
{
    // Constructor
}

MageTower::~MageTower()
{
    // Destructor
}

// Publics

void MageTower::update(float dt)
{
    updateTextureRect(level - 1, (Constants::TILE_SURFACE_HEIGHT / 3.0f));
}

std::optional<ProjectileData> MageTower::getShootData(float deltaTime)
{
    return std::nullopt;
}
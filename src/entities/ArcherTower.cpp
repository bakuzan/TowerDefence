#include "constants/Constants.h"
#include "ArcherTower.h"

ArcherTower::ArcherTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
                         sf::Vector2f position)
    : RangedTower(TowerType::ARCHER, texture, textureRects, position)
{
    // Constructor
}

ArcherTower::~ArcherTower()
{
    // Destructor
}

// Publics

void ArcherTower::update(float dt)
{
    updateTextureRect(level - 1, (Constants::TILE_SURFACE_HEIGHT / 4.0f));
}

std::optional<ProjectileData> ArcherTower::getShootData(float deltaTime)
{
    return std::nullopt;
}
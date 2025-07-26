#include "constants/Constants.h"
#include "MeleeTower.h"

MeleeTower::MeleeTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
                       sf::Vector2f position)
    : Tower(TowerType::MELEE, texture, textureRects, position)
{
    // Constructor
}

MeleeTower::~MeleeTower()
{
    // Destructor
}

// Publics

void MeleeTower::update(float dt)
{
    (void)dt; // ignored

    int textureIndex = calculateTextureIndex();
    updateTextureRect(textureIndex, (Constants::TILE_SURFACE_HEIGHT / 4.0f));
}

// Privates

int MeleeTower::calculateTextureIndex()
{
    int levelIndex = level - 1;
    return levelIndex * 2;
}
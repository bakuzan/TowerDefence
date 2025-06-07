#include "GameData.h"
#include "constants/Constants.h"

GameData::GameData()
{
    // Load textures
    textureManager.loadTexture(TextureId::ATLAS, "resources/images/Atlas_Spring.png");

    // Load audio
    // TODO

    // Load font
    if (!gameFont.loadFromFile("resources/fonts/PressStart2P-Regular.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }

    reset();
}

GameData::~GameData()
{
    // Destructor
}

// Publics

std::unordered_map<sf::Vector2i, TowerSpot> &GameData::getTowerSpots()
{
    return towerSpots;
}

void GameData::reset()
{
    towerSpots.clear();
}
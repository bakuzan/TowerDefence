#include "GameData.h"
#include "constants/Constants.h"

GameData::GameData()
{
    // Load textures
    textureManager.loadTexture(TextureId::ATLAS, "resources/images/Atlas_Spring.png");
    textureManager.loadTexture(TextureId::TOWERS, "resources/images/Towers.png");

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

const int GameData::getPlayerGold() const
{
    return playerGold;
}

void GameData::updatePlayerGold(int adjustment)
{
    playerGold = std::max(0, playerGold + adjustment);
}

const int GameData::getPlayerLives() const
{
    return playerLives;
}

void GameData::updatePlayerLives(int adjustment)
{
    playerLives = std::max(0, playerLives + adjustment);
}

const int GameData::getPlayerScore() const
{
    return playerScore;
}

void GameData::updatePlayerScore(int adjustment)
{
    playerScore = std::max(0, playerScore + adjustment);
}

void GameData::reset()
{
    towerSpots.clear();
    playerGold = 1000; // TODO 250
    playerLives = 10;
    playerScore = 0;
}
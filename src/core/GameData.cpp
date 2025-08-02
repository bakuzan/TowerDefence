#include "GameData.h"
#include "constants/Constants.h"

GameData::GameData()
{
    // Load textures
    textureManager.loadTexture(TextureId::ATLAS, "resources/images/Atlas.png");
    textureManager.loadTexture(TextureId::TOWERS, "resources/images/Towers.png");
    textureManager.loadTexture(TextureId::ENEMIES, "resources/images/Enemies.png");
    textureManager.loadTexture(TextureId::PROJECTILES, "resources/images/Projectiles.png");
    textureManager.loadTexture(TextureId::ICONS, "resources/images/Icons.png");
    textureManager.loadTexture(TextureId::SOLDIER, "resources/images/Soldiers.png");

    // Load audio
    // TODO

    // Load maps
    levelMapPaths.push_back("resources/maps/level_00.txt");
    levelMapPaths.push_back("resources/maps/level_01.txt");
    levelMapPaths.push_back("resources/maps/level_02.txt");

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

int GameData::getPlayerGold() const
{
    return playerGold;
}

void GameData::updatePlayerGold(int adjustment)
{
    playerGold = std::max(0, playerGold + adjustment);
}

int GameData::getPlayerLives() const
{
    return playerLives;
}

void GameData::updatePlayerLives(int adjustment)
{
    playerLives = std::max(0, playerLives + adjustment);
}

int GameData::getPlayerScore() const
{
    return playerScore;
}

void GameData::updatePlayerScore(int adjustment)
{
    playerScore = std::max(0, playerScore + adjustment);
}

std::vector<std::unique_ptr<Enemy>> &GameData::getEnemies()
{
    return enemies;
}

std::vector<std::unique_ptr<Projectile>> &GameData::getProjectiles()
{
    return projectiles;
}

std::vector<std::shared_ptr<Soldier>> &GameData::getSoldiers()
{
    return soldiers;
}

std::string GameData::getLevelMap(int index)
{
    if (hasLevelMap(index))
    {
        return levelMapPaths[index];
    }

    return levelMapPaths[0]; // Fallback
}

bool GameData::hasLevelMap(int index)
{
    return index >= 0 &&
           index < static_cast<int>(levelMapPaths.size());
}

void GameData::resetLevel()
{
    towerSpots.clear();
}

void GameData::reset()
{
    towerSpots.clear();
    enemies.clear();
    projectiles.clear();

    playerGold = 1000; // TODO 250
    playerLives = 10;
    playerScore = 0;
}
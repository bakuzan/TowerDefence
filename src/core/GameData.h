#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <unordered_map>
#include <vector>

#include "TextureManager.h"
#include "AudioManager.h"
#include "components/TextureRectManager.h"
#include "data/TowerSpot.h"
#include "entities/Enemy.h"
#include "entities/Projectile.h"
#include "utils/HashUtilities.h"

class GameData
{
private:
    std::unordered_map<sf::Vector2i, TowerSpot> towerSpots;
    int playerGold;
    int playerLives;
    int playerScore;

    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Projectile>> projectiles;
    std::vector<std::string> levelMapPaths;

public:
    sf::Font gameFont;

    TextureManager textureManager;
    AudioManager audioManager;

    TextureRectManager rectManager;

public:
    GameData();
    ~GameData();

    std::unordered_map<sf::Vector2i, TowerSpot> &getTowerSpots();

    const int getPlayerGold() const;
    void updatePlayerGold(int adjustment);

    const int getPlayerLives() const;
    void updatePlayerLives(int adjustment);

    const int getPlayerScore() const;
    void updatePlayerScore(int adjustment);

    std::vector<std::unique_ptr<Enemy>> &getEnemies();
    std::vector<std::unique_ptr<Projectile>> &getProjectiles();
    std::string getLevelMap(int index);
    bool hasLevelMap(int index);

    void resetLevel();
    void reset();
};

#endif // GAMEDATA_H

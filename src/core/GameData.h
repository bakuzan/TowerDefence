#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <unordered_map>
#include <vector>

#include "TextureManager.h"
// #include "AudioManager.h"
#include "components/TextureRectManager.h"
#include "data/TowerSpot.h"
#include "entities/Enemy.h"
#include "entities/Projectile.h"
#include "entities/Soldier.h"
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
    std::vector<std::shared_ptr<Soldier>> soldiers;
    std::vector<std::string> levelMapPaths;

public:
    sf::Font gameFont;

    TextureManager textureManager;
    // AudioManager audioManager;

    TextureRectManager rectManager;

public:
    GameData();
    ~GameData();

    std::unordered_map<sf::Vector2i, TowerSpot> &getTowerSpots();

    int getPlayerGold() const;
    void updatePlayerGold(int adjustment);

    int getPlayerLives() const;
    void updatePlayerLives(int adjustment);

    int getPlayerScore() const;
    void updatePlayerScore(int adjustment);

    std::vector<std::unique_ptr<Enemy>> &getEnemies();
    std::vector<std::unique_ptr<Projectile>> &getProjectiles();
    std::vector<std::shared_ptr<Soldier>> &getSoldiers();
    std::string getLevelMap(int index);
    bool hasLevelMap(int index);

    void resetLevel();
    void reset();
};

#endif // GAMEDATA_H

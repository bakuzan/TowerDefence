#ifndef ENEMYSPAWNMANAGER_H
#define ENEMYSPAWNMANAGER_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "components/TextureRectManager.h"
#include "data/SpawnGroup.h"
#include "data/SpawnInstruction.h"
#include "entities/Enemy.h"

class EnemySpawnManager
{
private:
    const TextureRectManager &enemyRectManager;
    const sf::Texture &texture;

    std::vector<SpawnInstruction> schedule;
    std::size_t nextSpawnIndex = 0;
    float timeSinceLastSpawn = 0.f;

private:
    sf::Vector2f selectSpawnPoint(const std::vector<sf::Vector2f> &spawnPoints);

public:
    EnemySpawnManager(const TextureRectManager &textureRectManager,
                      const sf::Texture &enemyTexture);
    ~EnemySpawnManager();

    void setWave(const std::vector<SpawnGroup> &groups);
    void spawnEnemies(float dt,
                      const std::vector<sf::Vector2f> spawnPoints,
                      std::vector<std::unique_ptr<Enemy>> &enemies);

    bool isWaveActive() const;
};

#endif // ENEMYSPAWNMANAGER_H

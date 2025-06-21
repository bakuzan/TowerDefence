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

public:
    EnemySpawnManager(const TextureRectManager &textureRectManager,
                      const sf::Texture &enemyTexture);
    ~EnemySpawnManager();

    void setWave(const std::vector<SpawnGroup> &groups);
    void spawnEnemies(float dt, std::vector<std::unique_ptr<Enemy>> &enemies);

    bool isWaveActive() const;
};

#endif // ENEMYSPAWNMANAGER_H

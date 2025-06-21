#include "EnemySpawnManager.h"

EnemySpawnManager::EnemySpawnManager(const TextureRectManager &textureRectManager,
                                     const sf::Texture &enemyTexture)
    : enemyRectManager(textureRectManager),
      texture(enemyTexture)
{
    // Constructor
}

EnemySpawnManager::~EnemySpawnManager()
{
    // Destructor
}

// Publics

void EnemySpawnManager::setWave(const std::vector<SpawnGroup> &groups)
{
    schedule.clear();
    nextSpawnIndex = 0;
    timeSinceLastSpawn = 0.f;

    for (const auto &group : groups)
    {
        float delay = group.initialDelay;
        for (int i = 0; i < group.count; ++i)
        {
            schedule.push_back({group.type, delay, group.stats});
            delay = group.interval; // Only use initial delay once
        }
    }
}

void EnemySpawnManager::spawnEnemies(float dt,
                                     std::vector<std::unique_ptr<Enemy>> &enemies)
{
    if (nextSpawnIndex >= schedule.size())
    {
        return;
    }

    timeSinceLastSpawn += dt;
    const auto &next = schedule[nextSpawnIndex];

    if (timeSinceLastSpawn >= next.delayAfterPrevious)
    {
        auto enemy = std::make_unique<Enemy>(
            texture,
            rectManager.getTextureRect(next.type),
            next.type,
            next.stats);

        enemies.push_back(std::move(enemy));

        timeSinceLastSpawn = 0.f;
        ++nextSpawnIndex;
    }
}

bool EnemySpawnManager::isWaveActive() const
{
    return nextSpawnIndex < schedule.size();
}
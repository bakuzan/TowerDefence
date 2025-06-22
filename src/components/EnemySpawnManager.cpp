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
                                     const std::vector<sf::Vector2f> spawnPoints,
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
            next.type,
            texture,
            enemyRectManager.getTextureRect(next.type),
            next.stats,
            selectSpawnPoint(spawnPoints));

        enemies.push_back(std::move(enemy));

        timeSinceLastSpawn = 0.f;
        ++nextSpawnIndex;
    }
}

bool EnemySpawnManager::isWaveActive() const
{
    return nextSpawnIndex < schedule.size();
}

// Privates

sf::Vector2f EnemySpawnManager::selectSpawnPoint(const std::vector<sf::Vector2f> &spawnPoints)
{
    std::size_t index = static_cast<std::size_t>(std::rand() % spawnPoints.size());
    return spawnPoints[index];
}

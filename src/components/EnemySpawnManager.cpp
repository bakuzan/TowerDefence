#include <cassert>

#include "EnemySpawnManager.h"

EnemySpawnManager::EnemySpawnManager(const TextureRectManager &textureRectManager,
                                     const sf::Texture &enemyTexture)
    : enemyRectManager(textureRectManager),
      texture(enemyTexture),
      rng(std::random_device{}())
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
                                     const PathMap &pathOptions,
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
            selectMapPath(pathOptions));

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

const std::vector<sf::Vector2f> &EnemySpawnManager::selectMapPath(
    const PathMap &pathOptions)
{
    assert(!pathOptions.empty() &&
           "selectMapPath: pathOptions is empty — no paths to select from.");

    std::uniform_int_distribution<size_t> dist(0, pathOptions.size() - 1);
    auto it = pathOptions.begin();
    std::advance(it, dist(rng));
    return it->second;
}

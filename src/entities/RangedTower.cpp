#include <cmath>

#include "RangedTower.h"
#include "utils/GameUtils.h"

RangedTower::RangedTower(TowerType towerType,
                         const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
                         sf::Vector2f position)
    : Tower(towerType, texture, textureRects, position),
      timeSinceLastShot(0.0f)
{
    // Constructor
}

RangedTower::~RangedTower()
{
    // Destructor
}

// Protected

bool RangedTower::isCooldownReady(float deltaTime, float cooldown)
{
    timeSinceLastShot += deltaTime;

    if (timeSinceLastShot >= cooldown)
    {
        return true;
    }

    return false;
}

Enemy *RangedTower::acquireTarget(const std::vector<std::unique_ptr<Enemy>> &enemies,
                                  float range)
{
    Enemy *nearest = nullptr;
    float minDistance = range;

    for (const auto &enemy : enemies)
    {
        float distance = GameUtils::calculateEuclideanDistance(sprite.getPosition(),
                                                               enemy->getSprite().getPosition());

        if (distance <= minDistance)
        {
            minDistance = distance;
            nearest = enemy.get();
        }
    }

    return nearest;
}

Enemy *RangedTower::tryAcquireTargetAndCooldown(float deltaTime,
                                                float cooldown,
                                                float range,
                                                const std::vector<std::unique_ptr<Enemy>> &enemies)
{
    if (!isCooldownReady(deltaTime, cooldown))
    {
        return nullptr;
    }

    Enemy *target = acquireTarget(enemies, range);

    if (!target)
    {
        return nullptr;
    }

    timeSinceLastShot = 0.0f;
    return target;
}

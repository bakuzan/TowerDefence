#include <cmath>

#include "ArrowProjectile.h"
#include "utils/GameUtils.h"

ArrowProjectile::ArrowProjectile(ProjectileType type,
                                 const sf::Texture &texture, sf::IntRect textureRect,
                                 sf::Vector2f spawnPosition,
                                 sf::Vector2f targetPosition,
                                 float travelTime,
                                 float speed,
                                 int damage)
    : Projectile(type,
                 texture, textureRect,
                 spawnPosition,
                 speed,
                 damage),
      spawnPos(spawnPosition),
      targetPos(targetPosition),
      totalTimeToTarget(travelTime),
      elapsedTime(0.0f)
{
    // Constructor
}

ArrowProjectile::~ArrowProjectile()
{
    // Destructor
}

// Publics

void ArrowProjectile::update(float deltaTime,
                             const std::vector<std::unique_ptr<Enemy>> &enemies)
{
    elapsedTime += deltaTime;

    float t = elapsedTime / totalTimeToTarget;
    if (t >= 1.0f)
    {
        t = 1.0f;
        canRemove = true;
    }

    float flightDistance = GameUtils::calculateEuclideanDistance(spawnPos, targetPos);
    float arcHeight = std::clamp(flightDistance * 0.25f, 50.f, 200.f);

    sf::Vector2f linearPos = spawnPos + (targetPos - spawnPos) * t;
    float heightOffset = 4 * arcHeight * t * (1 - t); // Parabola
    sf::Vector2f currentPos = {linearPos.x, linearPos.y - heightOffset};

    sprite.setPosition(currentPos);

    // Apply rotation to arrow point correctly
    if (t > 0.0f)
    {
        sf::Vector2f previousLinearPos = spawnPos + (targetPos - spawnPos) * (t - deltaTime / totalTimeToTarget);
        float previousHeightOffset = 4 * arcHeight * (t - deltaTime / totalTimeToTarget) * (1 - (t - deltaTime / totalTimeToTarget));
        sf::Vector2f previousPos = {previousLinearPos.x, previousLinearPos.y - previousHeightOffset};

        sf::Vector2f direction = currentPos - previousPos;
        float angleRadians = std::atan2(direction.y, direction.x);
        float angleDegrees = angleRadians * 180.0f / 3.14159265f;

        sprite.setRotation(angleDegrees + rotationOffset);
    }
}

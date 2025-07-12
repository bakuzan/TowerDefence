#ifndef ARROWPROJECTILE_H
#define ARROWPROJECTILE_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "constants/Identifiers.h"
#include "constants/ProjectileType.h"
#include "entities/Enemy.h"
#include "entities/Projectile.h"

class ArrowProjectile : public Projectile
{
private:
    sf::Vector2f spawnPos;
    sf::Vector2f targetPos;
    float totalTimeToTarget;
    float elapsedTime;

    static constexpr float rotationOffset = 90.0f;

public:
    ArrowProjectile(ProjectileType type,
                    const sf::Texture &texture, sf::IntRect textureRect,
                    sf::Vector2f spawnPosition,
                    sf::Vector2f targetPosition,
                    float travelTime,
                    float speed,
                    int damage);
    ~ArrowProjectile() override;

    void update(float deltaTime,
                const std::vector<std::unique_ptr<Enemy>> &enemies) override;
};

#endif // ARROWPROJECTILE_H

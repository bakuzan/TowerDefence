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
    sf::Vector2f direction;

public:
    ArrowProjectile(ProjectileType type,
                    const sf::Texture &texture, sf::IntRect textureRect,
                    sf::Vector2f spawnPosition,
                    float speed,
                    int damage,
                    sf::Vector2f dir);
    ~ArrowProjectile() override;

    void update(float deltaTime,
                const std::vector<std::unique_ptr<Enemy>> &enemies) override;
};

#endif // ARROWPROJECTILE_H

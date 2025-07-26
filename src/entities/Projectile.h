#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "constants/ProjectileType.h"
#include "entities/Enemy.h"

class Projectile
{
protected:
    ProjectileType type;
    sf::Sprite sprite;

    float speed;
    int damage;

    bool canRemove;

public:
    Projectile(ProjectileType projectileType,
               const sf::Texture &texture, sf::IntRect textureRect,
               sf::Vector2f spawnPosition,
               float speed,
               int damage);
    virtual ~Projectile() = default;

    virtual void update(float deltaTime, const std::vector<std::unique_ptr<Enemy>> &enemies) = 0;
    void render(sf::RenderWindow &window) const;

    int getDamageInflicts() const;
    const sf::Sprite &getSprite() const;
    bool canBeRemoved() const;
};

#endif // PROJECTILE_H

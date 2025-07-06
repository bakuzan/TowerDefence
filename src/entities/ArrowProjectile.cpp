#include "ArrowProjectile.h"

ArrowProjectile::ArrowProjectile(ProjectileType type,
                                 const sf::Texture &texture, sf::IntRect textureRect,
                                 sf::Vector2f spawnPosition,
                                 float speed,
                                 int damage,
                                 sf::Vector2f dir)
    : Projectile(type,
                 texture, textureRect,
                 spawnPosition,
                 speed,
                 damage),
      direction(dir)
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
    sprite.move(direction * speed * deltaTime);
    // TODO change this so it is stylised guaranteed hit
}

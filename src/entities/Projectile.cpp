#include "Projectile.h"

Projectile::Projectile(ProjectileType projectileType,
                       const sf::Texture &texture, sf::IntRect textureRect,
                       sf::Vector2f spawnPosition,
                       float speed,
                       int damage)
    : type(projectileType),
      speed(speed), damage(damage),
      canRemove(false)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    sprite.setPosition(spawnPosition);
}

// Publics

void Projectile::render(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

int Projectile::getDamageInflicts() const
{
    return damage;
}

const sf::Sprite &Projectile::getSprite() const
{
    return sprite;
}

bool Projectile::canBeRemoved() const
{
    return canRemove;
}
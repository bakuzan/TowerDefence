#include "Enemy.h"

Enemy::Enemy(EnemyType enemyType,
             const sf::Texture &texture, const sf::IntRect &textureRect,
             sf::Vector2f spawnPosition)
    : type(enemyType)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    sprite.setPosition(spawnPosition);
}

Enemy::~Enemy()
{
    // Destructor
}

// Publics

void Enemy::render(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

const EnemyType Enemy::getType() const
{
    return type;
}
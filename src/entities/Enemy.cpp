#include "Enemy.h"

Enemy::Enemy(EnemyType enemyType,
             const sf::Texture &texture, const sf::IntRect &textureRect,
             EnemyStats enemyStats,
             sf::Vector2f spawnPosition)
    : type(enemyType),
      initialStats(enemyStats), stats(enemyStats)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    sprite.setOrigin(textureRect.width / 2.f, textureRect.height / 2.f);
    sprite.setPosition(spawnPosition.x, spawnPosition.y - (textureRect.height / 4.f));
}

Enemy::~Enemy()
{
    // Destructor
}

// Publics

void Enemy::update(float dt)
{
}

void Enemy::render(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

const EnemyType Enemy::getType() const
{
    return type;
}

const sf::Sprite &Enemy::getSprite() const
{
    return sprite;
}
#include <cmath>

#include "Enemy.h"

Enemy::Enemy(EnemyType enemyType,
             const sf::Texture &texture, const sf::IntRect &textureRect,
             EnemyStats enemyStats,
             const std::vector<sf::Vector2f> &mapPath)
    : type(enemyType),
      initialStats(enemyStats), stats(enemyStats),
      path(mapPath), currentPathIndex(0)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    sprite.setOrigin(textureRect.width / 2.f, textureRect.height / 2.f);

    if (!path.empty())
    {
        sprite.setPosition(path[currentPathIndex].x,
                           path[currentPathIndex].y - (textureRect.height / 4.f));
    }
}

Enemy::~Enemy()
{
    // Destructor
}

// Publics

void Enemy::update(float dt)
{
    if (currentPathIndex + 1 >= path.size())
    {
        // TODO Flag this so enemy can be removed and damage the player
        return;
    }

    sf::Vector2f currentPos = sprite.getPosition();
    sf::Vector2f target = path[currentPathIndex + 1];
    target.y -= sprite.getTextureRect().height / 4.f;

    sf::Vector2f direction = target - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 1.f)
    {
        currentPathIndex++;
        return;
    }

    sf::Vector2f normalized = direction / distance;
    sf::Vector2f movement = normalized * stats.speed * dt;
    sprite.move(movement);
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

bool Enemy::hasReachedGoal() const
{
    return currentPathIndex + 1 >= path.size();
}

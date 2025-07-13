#include <cmath>

#include "Enemy.h"
#include "utils/GameUtils.h"

Enemy::Enemy(EnemyID enemyId, EnemyType enemyType,
             const sf::Texture &texture, const sf::IntRect &textureRect,
             EnemyStats enemyStats,
             const std::vector<sf::Vector2f> &mapPath)
    : id(enemyId),
      type(enemyType),
      initialStats(enemyStats), stats(enemyStats),
      path(mapPath), currentPathIndex(0),
      damageFeedbackTimer(0.0f)
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
        // Do need to do anything, the enemy has reached its goal.
        return;
    }

    sf::Vector2f currentPos = sprite.getPosition();
    sf::Vector2f target = getCurrentTargetPosition();

    sf::Vector2f direction = target - currentPos;
    float distance = GameUtils::calculateEuclideanDistance(currentPos, target);

    if (distance < 1.f)
    {
        currentPathIndex++;
        return;
    }

    sf::Vector2f normalized = direction / distance;
    sf::Vector2f movement = normalized * stats.speed * dt;
    sprite.move(movement);

    // Visual feedback for taking damage
    if (damageFeedbackTimer > 0.0f)
    {
        damageFeedbackTimer -= dt;
        sprite.setColor(sf::Color(240, 61, 61)); // Red tint
    }
    else
    {
        sprite.setColor(sf::Color(255, 255, 255)); // Normal
    }
}

void Enemy::render(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

const EnemyID Enemy::getID() const
{
    return id;
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

const int Enemy::getHealth() const
{
    return stats.health;
}

void Enemy::applyDamage(int adjustment)
{
    stats.health = std::max(0, stats.health - adjustment);
    damageFeedbackTimer = damageFlashDuration;
}

const int Enemy::getPointsValue() const
{
    return stats.pointsValue;
}

sf::Vector2f Enemy::getVelocity() const
{
    if (currentPathIndex + 1 >= path.size())
    {
        return {0.f, 0.f};
    }

    sf::Vector2f currentPos = sprite.getPosition();
    sf::Vector2f target = getCurrentTargetPosition();

    sf::Vector2f direction = target - currentPos;
    float distance = GameUtils::calculateEuclideanDistance(currentPos, target);

    if (distance == 0.f)
    {
        return {0.f, 0.f};
    }

    sf::Vector2f normalized = direction / distance;
    return normalized * stats.speed;
}

// Privates

sf::Vector2f Enemy::getCurrentTargetPosition() const
{
    sf::Vector2f target = path[currentPathIndex + 1];
    target.y -= sprite.getTextureRect().height / 4.f;
    return target;
}
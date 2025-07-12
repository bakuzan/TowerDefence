#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "constants/Identifiers.h"
#include "constants/EnemyType.h"
#include "data/EnemyStats.h"

class Enemy
{
protected:
    EnemyID id;
    EnemyType type;
    sf::Sprite sprite;

    EnemyStats initialStats;
    EnemyStats stats;

    const std::vector<sf::Vector2f> &path;
    size_t currentPathIndex;

private:
    sf::Vector2f getCurrentTargetPosition() const;

public:
    Enemy(EnemyID enemyId, EnemyType enemyType,
          const sf::Texture &texture, const sf::IntRect &textureRect,
          EnemyStats enemyStats,
          const std::vector<sf::Vector2f> &mapPath);
    ~Enemy();

    virtual void update(float dt);
    void render(sf::RenderWindow &window) const;

    const EnemyID getID() const;
    const EnemyType getType() const;
    const sf::Sprite &getSprite() const;
    bool hasReachedGoal() const;

    const int getHealth() const;
    void updateHealth(int adjustment);

    const int getPointsValue() const;
    sf::Vector2f getVelocity() const;
};

#endif // ENEMY_H

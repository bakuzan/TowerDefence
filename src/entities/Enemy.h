#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "constants/EnemyType.h"
#include "data/EnemyStats.h"

class Enemy
{
protected:
    EnemyType type;
    sf::Sprite sprite;

    EnemyStats initialStats;
    EnemyStats stats;

    const std::vector<sf::Vector2f> &path;
    size_t currentPathIndex;

public:
    Enemy(EnemyType enemyType,
          const sf::Texture &texture, const sf::IntRect &textureRect,
          EnemyStats enemyStats,
          const std::vector<sf::Vector2f> &mapPath);
    ~Enemy();

    virtual void update(float dt);
    void render(sf::RenderWindow &window) const;

    const EnemyType getType() const;
    const sf::Sprite &getSprite() const;
    bool hasReachedGoal() const;
};

#endif // ENEMY_H

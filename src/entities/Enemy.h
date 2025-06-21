#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "constants/EnemyType.h"

class Enemy
{
protected:
    EnemyType type;
    sf::Sprite sprite;

public:
    Enemy(EnemyType enemyType,
          const sf::Texture &texture, const sf::IntRect &textureRect,
          sf::Vector2f spawnPosition);
    ~Enemy();

    virtual void update(float dt) = 0;
    void render(sf::RenderWindow &window) const;

    const EnemyType getType() const;
};

#endif // ENEMY_H

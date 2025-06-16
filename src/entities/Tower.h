#ifndef TOWER_H
#define TOWER_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "constants/TowerType.h"

class Tower
{
protected:
    TowerType type;
    int level;

    const std::vector<sf::IntRect> &textureRects;
    sf::Sprite sprite;
    sf::Vector2f tileOriginPosition;

protected:
    void updateTextureRect(int textureIndex, float verticalOffset);

public:
    Tower(TowerType towerType,
          const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
          sf::Vector2f position);
    ~Tower();

    virtual void update(float dt) = 0;
    void render(sf::RenderWindow &window) const;

    const int getLevel() const;
    const TowerType getType() const;

    void levelUp();
};

#endif // TOWER_H

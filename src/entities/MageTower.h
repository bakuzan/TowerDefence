#ifndef MAGETOWER_H
#define MAGETOWER_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "Tower.h"

class MageTower : public Tower
{
public:
    MageTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
              sf::Vector2f position);
    ~MageTower();

    void update(float dt) override;
};

#endif // MAGETOWER_H

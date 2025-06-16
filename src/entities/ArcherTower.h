#ifndef ARCHERTOWER_H
#define ARCHERTOWER_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "Tower.h"

class ArcherTower : public Tower
{
public:
    ArcherTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
                sf::Vector2f position);
    ~ArcherTower();

    void update(float dt) override;
};

#endif // ARCHERTOWER_H

#ifndef MELEETOWER_H
#define MELEETOWER_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "Tower.h"

class MeleeTower : public Tower
{
private:
    int calculateTextureIndex();

public:
    MeleeTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
               sf::Vector2f position);
    ~MeleeTower();

    void update(float dt) override;
};

#endif // MELEETOWER_H

#ifndef MAGETOWER_H
#define MAGETOWER_H

#include <SFML/Graphics.hpp>

#include <optional>
#include <vector>

#include "data/ProjectileData.h"
#include "entities/RangedTower.h"

class MageTower : public RangedTower
{
public:
    MageTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
              sf::Vector2f position);
    ~MageTower();

    void update(float dt) override;

    std::optional<ProjectileData> getShootData(float deltaTime) override;
};

#endif // MAGETOWER_H

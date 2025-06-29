#ifndef RANGEDTOWER_H
#define RANGEDTOWER_H

#include <SFML/Graphics.hpp>

#include <optional>
#include <vector>

#include "constants/TowerType.h"
#include "data/ProjectileData.h"
#include "entities/Tower.h"

class RangedTower : public Tower
{
public:
    RangedTower(TowerType towerType,
                const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
                sf::Vector2f position);
    ~RangedTower() override;

    virtual std::optional<ProjectileData> getShootData(float deltaTime) = 0;
};

#endif // RANGEDTOWER_H

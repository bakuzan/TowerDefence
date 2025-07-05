#ifndef MAGETOWER_H
#define MAGETOWER_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <optional>
#include <vector>

#include "data/ProjectileData.h"
#include "entities/Enemy.h"
#include "entities/RangedTower.h"

class MageTower : public RangedTower
{
private:
    float timeSinceLastShot;

public:
    MageTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
              sf::Vector2f position);
    ~MageTower();

    void update(float dt) override;

    std::optional<ProjectileData> getShootData(float deltaTime,
                                               const std::vector<std::unique_ptr<Enemy>> &enemies) override;
};

#endif // MAGETOWER_H

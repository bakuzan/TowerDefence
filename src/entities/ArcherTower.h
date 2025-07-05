#ifndef ARCHERTOWER_H
#define ARCHERTOWER_H

#include <SFML/Graphics.hpp>

#include <optional>
#include <vector>

#include "data/ProjectileData.h"
#include "entities/RangedTower.h"

class ArcherTower : public RangedTower
{
private:
    float timeSinceLastShot;

public:
    ArcherTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
                sf::Vector2f position);
    ~ArcherTower();

    void update(float dt) override;

    std::optional<ProjectileData> getShootData(float deltaTime,
                                               const std::vector<std::unique_ptr<Enemy>> &enemies) override;
};

#endif // ARCHERTOWER_H

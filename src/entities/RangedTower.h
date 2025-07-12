#ifndef RANGEDTOWER_H
#define RANGEDTOWER_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <optional>
#include <vector>

#include "constants/TowerType.h"
#include "data/ProjectileData.h"
#include "entities/Enemy.h"
#include "entities/Tower.h"

class RangedTower : public Tower
{
protected:
    float timeSinceLastShot;

protected:
    bool isCooldownReady(float deltaTime, float cooldown);
    Enemy *acquireTarget(const std::vector<std::unique_ptr<Enemy>> &enemies,
                         float range);
    Enemy *tryAcquireTargetAndCooldown(float deltaTime,
                                       float cooldown,
                                       float range,
                                       const std::vector<std::unique_ptr<Enemy>> &enemies);

public:
    RangedTower(TowerType towerType,
                const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
                sf::Vector2f position);
    ~RangedTower() override;

    virtual std::optional<ProjectileData> getShootData(float deltaTime,
                                                       const std::vector<std::unique_ptr<Enemy>> &enemies) = 0;
};

#endif // RANGEDTOWER_H

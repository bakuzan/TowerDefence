#ifndef MELEETOWER_H
#define MELEETOWER_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <optional>
#include <vector>

#include "Soldier.h"
#include "Tower.h"
#include "data/SoldierSpawnData.h"

class MeleeTower : public Tower
{
private:
    std::weak_ptr<Soldier> deployedSoldier;
    float spawnCooldownTimer = 0.0f;
    float spawnCooldown = 3.0f;

private:
    int calculateTextureIndex();

public:
    MeleeTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
               sf::Vector2f position);
    ~MeleeTower();

    void update(float dt) override;

    std::optional<SoldierSpawnData> getSoldierData(float dt);
    void setDeployedSoldier(const std::shared_ptr<Soldier> &soldier);
};

#endif // MELEETOWER_H

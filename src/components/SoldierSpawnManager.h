#ifndef SOLDIERSPAWNMANAGER_H
#define SOLDIERSPAWNMANAGER_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "components/TextureRectManager.h"
#include "data/SoldierSpawnData.h"
#include "entities/Soldier.h"

class SoldierSpawnManager
{
private:
    const TextureRectManager &rectManager;

public:
    SoldierSpawnManager(const TextureRectManager &textureRectManager);
    ~SoldierSpawnManager();

    std::shared_ptr<Soldier> spawnSoldier(
        const sf::Texture &texture,
        std::vector<std::shared_ptr<Soldier>> &soldiers,
        const SoldierSpawnData &data,
        const sf::Vector2f &targetPosition);
};

#endif // SOLDIERSPAWNMANAGER_H

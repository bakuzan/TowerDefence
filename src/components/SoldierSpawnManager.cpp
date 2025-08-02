#include "SoldierSpawnManager.h"

SoldierSpawnManager::SoldierSpawnManager(const TextureRectManager &textureRectManager)
    : rectManager(textureRectManager)
{
    // Constructor
}

SoldierSpawnManager::~SoldierSpawnManager()
{
    // Destructor
}

// Publics

std::shared_ptr<Soldier> SoldierSpawnManager::spawnSoldier(
    const sf::Texture &texture,
    std::vector<std::shared_ptr<Soldier>> &soldiers,
    const SoldierSpawnData &data,
    const sf::Vector2f &targetPosition)
{
    auto soldier = std::make_shared<Soldier>(texture, rectManager.getTextureRect(data.type),
                                             data.spawnPosition, targetPosition,
                                             data.health,
                                             data.attackDamage, data.attackSpeed);

    soldiers.push_back(soldier);
    return soldier;
}

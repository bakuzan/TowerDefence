#include "TrayOptionManager.h"

#include "constants/Constants.h"
#include "constants/TileId.h"
#include "constants/TowerChange.h"
#include "constants/TowerType.h"
#include "constants/TextureId.h"

TrayOptionManager::TrayOptionManager(const TextureManager &tm,
                                     const TextureRectManager &rm)
    : textureManager(tm),
      rectManager(rm)
{
    towerCosts[TowerType::MELEE] = 50;
    towerCosts[TowerType::ARCHER] = 75;
    towerCosts[TowerType::MAGE] = 100;
}

TrayOptionManager::~TrayOptionManager()
{
    // Destructor
}

// Publics

std::vector<TrayOption> TrayOptionManager::getTrayOptions(
    TowerSpot &spot,
    int playerGold,
    std::function<void(int)> selectionCallback)
{
    return spot.hasTower()
               ? getTowerOptions(spot, playerGold, selectionCallback)
               : getPlacementOptions(playerGold, selectionCallback);
}

const int TrayOptionManager::getOptionCost(TowerType towerType) const
{
    return towerCosts.at(towerType);
}

const int TrayOptionManager::getOptionCost(TowerSpot &spot) const
{
    return getUpgradeCost(*spot.tower);
}

const int TrayOptionManager::getRemoveValue(TowerSpot &spot) const
{
    int towerValue = towerCosts.at(spot.tower->getType()) * (spot.tower->getLevel());
    return static_cast<int>(towerValue * REMOVE_MULTIPLIER);
}

// Privates

std::vector<TrayOption> TrayOptionManager::getPlacementOptions(
    int playerGold,
    std::function<void(int)> selectionCallback)
{
    std::vector<TrayOption> trayOptions;
    int meleeTowerCost = towerCosts.at(TowerType::MELEE);
    int archerTowerCost = towerCosts.at(TowerType::ARCHER);
    int mageTowerCost = towerCosts.at(TowerType::MAGE);

    trayOptions.push_back(
        TrayOption::Create(textureManager.getTexture(TextureId::TOWERS),
                           rectManager.getTextureRect(TowerType::MELEE),
                           "Melee Tower",
                           meleeTowerCost,
                           static_cast<int>(TowerType::MELEE),
                           meleeTowerCost > playerGold,
                           selectionCallback));
    trayOptions.push_back(
        TrayOption::Create(textureManager.getTexture(TextureId::TOWERS),
                           rectManager.getTextureRect(TowerType::ARCHER),
                           "Archer Tower",
                           archerTowerCost,
                           static_cast<int>(TowerType::ARCHER),
                           archerTowerCost > playerGold,
                           selectionCallback));
    trayOptions.push_back(
        TrayOption::Create(textureManager.getTexture(TextureId::TOWERS),
                           rectManager.getTextureRect(TowerType::MAGE),
                           "Mage Tower",
                           mageTowerCost,
                           static_cast<int>(TowerType::MAGE),
                           mageTowerCost > playerGold,
                           selectionCallback));

    return trayOptions;
}

std::vector<TrayOption> TrayOptionManager::getTowerOptions(
    TowerSpot &spot,
    int playerGold,
    std::function<void(int)> selectionCallback)
{
    std::vector<TrayOption> trayOptions;

    if (spot.isUpgradeable())
    {
        TowerType towerType = spot.tower->getType();
        int upgradeCost = getUpgradeCost(*spot.tower);
        int textureRectIndex = towerType == TowerType::MELEE
                                   ? spot.tower->getLevel() * 2
                                   : spot.tower->getLevel();

        trayOptions.push_back(
            TrayOption::Create(textureManager.getTexture(TextureId::TOWERS),
                               rectManager.getTextureRect(towerType, textureRectIndex),
                               "Upgrade Tower",
                               upgradeCost,
                               static_cast<int>(TowerChange::UPGRADE),
                               upgradeCost > playerGold,
                               selectionCallback));
    }

    trayOptions.push_back(
        TrayOption::Create(textureManager.getTexture(TextureId::ATLAS),
                           sf::IntRect(static_cast<int>(TileId::TOWER_SPOT) * Constants::TILE_WIDTH, 0, Constants::TILE_WIDTH, Constants::TILE_HEIGHT),
                           "Sell Tower",
                           getRemoveValue(spot),
                           static_cast<int>(TowerChange::REMOVE),
                           false,
                           selectionCallback));

    return trayOptions;
}

const int TrayOptionManager::getUpgradeCost(const Tower &tower) const
{
    return towerCosts.at(tower.getType()) * (tower.getLevel() + 1);
}

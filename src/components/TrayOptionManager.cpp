#include "TrayOptionManager.h"

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
    // TODO Need to add remove handling
    return getUpgradeCost(*spot.tower);
}

// Privates

std::vector<TrayOption> TrayOptionManager::getPlacementOptions(
    int playerGold,
    std::function<void(int)> selectionCallback)
{
    std::vector<TrayOption> trayOptions;

    trayOptions.push_back(TrayOption::Create(textureManager.getTexture(TextureId::TOWERS),
                                             rectManager.getTextureRect(TowerType::MELEE),
                                             "Melee Tower",
                                             towerCosts.at(TowerType::MELEE),
                                             static_cast<int>(TowerType::MELEE),
                                             selectionCallback));
    trayOptions.push_back(TrayOption::Create(textureManager.getTexture(TextureId::TOWERS),
                                             rectManager.getTextureRect(TowerType::ARCHER),
                                             "Archer Tower",
                                             towerCosts.at(TowerType::ARCHER),
                                             static_cast<int>(TowerType::ARCHER),
                                             selectionCallback));
    trayOptions.push_back(TrayOption::Create(textureManager.getTexture(TextureId::TOWERS),
                                             rectManager.getTextureRect(TowerType::MAGE),
                                             "Mage Tower",
                                             towerCosts.at(TowerType::MAGE),
                                             static_cast<int>(TowerType::MAGE),
                                             selectionCallback));

    return trayOptions;
}

std::vector<TrayOption> TrayOptionManager::getTowerOptions(
    TowerSpot &spot,
    int playerGold,
    std::function<void(int)> selectionCallback)
{
    std::vector<TrayOption> trayOptions;

    trayOptions.push_back(TrayOption::Create(textureManager.getTexture(TextureId::TOWERS),
                                             rectManager.getTextureRect(spot.tower->getType(), spot.tower->getLevel()),
                                             "Upgrade Tower",
                                             getUpgradeCost(*spot.tower),
                                             0, selectionCallback));
    // TODO Upgrades settings...
    // trayOptions.push_back(TrayOption::Create(gameData.textureManager.getTexture("sell"),
    //                                          {128, 0, 64, 64},
    //                                          "Sell Tower", 3));

    return trayOptions;
}

const int TrayOptionManager::getUpgradeCost(const Tower &tower) const
{
    return towerCosts.at(tower.getType()) * (tower.getLevel() + 1);
}

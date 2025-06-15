#ifndef TRAYOPTIONMANAGER_H
#define TRAYOPTIONMANAGER_H

#include <functional>
#include <unordered_map>
#include <vector>

#include "constants/TowerType.h"
#include "components/TextureRectManager.h"
#include "core/TextureManager.h"
#include "data/TrayOption.h"
#include "data/TowerSpot.h"
#include "entities/Tower.h"

class TrayOptionManager
{
private:
    const TextureManager &textureManager;
    const TextureRectManager &rectManager;

    std::unordered_map<TowerType, int, TowerTypeHash> towerCosts;

    static constexpr float REMOVE_MULTIPLIER = 0.8f;

private:
    std::vector<TrayOption> getPlacementOptions(int playerGold, std::function<void(int)> selectionCallback);
    std::vector<TrayOption> getTowerOptions(TowerSpot &spot,
                                            int playerGold,
                                            std::function<void(int)> selectionCallback);

    const int getUpgradeCost(const Tower &tower) const;

public:
    TrayOptionManager(const TextureManager &tm,
                      const TextureRectManager &rm);
    ~TrayOptionManager();

    std::vector<TrayOption> getTrayOptions(TowerSpot &spot,
                                           int playerGold,
                                           std::function<void(int)> selectionCallback);

    const int getOptionCost(TowerType towerType) const;
    const int getOptionCost(TowerSpot &spot) const;
    const int getRemoveValue(TowerSpot &spot) const;
};

#endif // TRAYOPTIONMANAGER_H

#pragma once

#include <memory>

#include "constants/TowerType.h"
#include "entities/Tower.h"
#include "entities/MeleeTower.h"
#include "entities/ArcherTower.h"
#include "entities/MageTower.h"

struct TowerSpot
{
    std::unique_ptr<Tower> tower = nullptr;

    const bool hasTower() const
    {
        return tower != nullptr;
    }

    const bool isUpgradeable() const
    {
        return tower && tower->getLevel() < 3;
    }

    void placeTower(TowerType type)
    {
        switch (type)
        {
        case TowerType::MELEE:
            tower = std::make_unique<MeleeTower>();
            break;
        case TowerType::ARCHER:
            tower = std::make_unique<ArcherTower>();
            break;
        case TowerType::MAGE:
            tower = std::make_unique<MageTower>();
            break;
        }
    }

    void removeTower()
    {
        tower.reset();
    }
};
#pragma once

#include "entities/Tower.h"

struct TowerSpot
{
    Tower *tower = nullptr;

    bool hasTower()
    {
        return tower != nullptr;
    }

    bool isUpgradeable() const
    {
        return tower && tower->getLevel() < 3;
    }
};
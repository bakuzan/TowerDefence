#pragma once

#include "entities/Tower.h"

struct TowerSpot
{
    Tower *tower = nullptr;

    const bool hasTower() const
    {
        return tower != nullptr;
    }

    const bool isUpgradeable() const
    {
        return tower && tower->getLevel() < 3;
    }
};
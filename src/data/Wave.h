#pragma once

#include <vector>

#include "data/SpawnGroup.h"

struct Wave
{
    std::vector<SpawnGroup> spawnGroups;
    bool hasRun = false;

    static Wave create(std::vector<SpawnGroup> groups)
    {
        return Wave{groups, false};
    }
};
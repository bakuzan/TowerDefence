#pragma once

#include <vector>

#include "data/SpawnGroup.h"

struct Wave
{
    std::vector<SpawnGroup> spawnGroups;
    bool hasRun = false;

    static Wave create(std::initializer_list<SpawnGroup> groups)
    {
        return Wave{std::vector<SpawnGroup>{groups}, false};
    }
};
#pragma once

#include "constants/EnemyType.h"
#include "data/EnemyStats.h"

struct EnemyArchetype
{
    EnemyType type;
    float cost;
    EnemyStats stats;
    float intervalMin;
    float intervalMax;
};
#pragma once

#include "constants/EnemyType.h"
#include "data/EnemyStats.h"

struct SpawnGroup
{
    EnemyType type;
    int count;
    float interval;
    float initialDelay;
    EnemyStats stats;
};
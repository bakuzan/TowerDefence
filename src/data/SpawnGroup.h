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

    static SpawnGroup create(EnemyType type,
                             int count, float interval, float delay = 0.0f,
                             EnemyStats stats = {})
    {
        return {type, count, interval, delay, stats};
    }
};
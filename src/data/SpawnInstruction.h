#pragma once

#include "constants/EnemyType.h"
#include "data/EnemyStats.h"

struct SpawnInstruction
{
    EnemyType type;
    float delayAfterPrevious;
    EnemyStats stats;
};

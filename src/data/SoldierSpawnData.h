#pragma once

#include <SFML/Graphics.hpp>

#include "constants/SoldierType.h"

struct SoldierSpawnData
{
    SoldierType type;
    sf::Vector2f spawnPosition;
    int health;
    int attackDamage;

    static SoldierSpawnData create(SoldierType soldierType,
                                   sf::Vector2f spawnPos,
                                   int health,
                                   int damage)
    {
        return {soldierType, spawnPos, health, damage};
    }
};

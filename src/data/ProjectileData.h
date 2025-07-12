#pragma once

#include <SFML/Graphics.hpp>

#include "constants/ProjectileType.h"
#include "constants/Identifiers.h"

struct ProjectileData
{
    ProjectileType type;
    sf::Vector2f spawnPosition;
    int damage;
    float speed = 0.f;

    // Optional for physics-based
    sf::Vector2f targetPosition = {0.f, 0.f};
    float timeToTarget = 0.0f;

    // Optional for guaranteed-hit
    EnemyID targetId = InvalidEnemyID;

    static ProjectileData createArrow(sf::Vector2f pos, sf::Vector2f trgt, float time, float spd, int dmg)
    {
        return ProjectileData{
            ProjectileType::ARROW,
            pos,
            dmg,
            spd,

            trgt,
            time,
            InvalidEnemyID};
    }

    static ProjectileData createMagic(sf::Vector2f pos, EnemyID target, float spd, int dmg)
    {
        return ProjectileData{
            ProjectileType::MAGIC,
            pos,
            dmg,
            spd,

            {},   // Omitted: direction
            0.0f, // Ommitted: time-to-target
            target};
    }
};

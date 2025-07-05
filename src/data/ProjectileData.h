#pragma once

#include <SFML/Graphics.hpp>

#include "constants/ProjectileType.h"
#include "constants/Identifiers.h"

struct ProjectileData
{
    ProjectileType type;
    sf::Vector2f spawnPosition;
    int damage;

    // Optional for physics-based
    sf::Vector2f direction = {0.f, 0.f};
    float speed = 0.f;

    // Optional for guaranteed-hit
    EnemyID targetId = InvalidEnemyID;

    static ProjectileData createArrow(sf::Vector2f pos, sf::Vector2f dir, float spd, int dmg)
    {
        return ProjectileData{
            ProjectileType::ARROW,
            pos,
            dmg,
            dir,
            spd,
            InvalidEnemyID};
    }

    static ProjectileData createMagic(sf::Vector2f pos, EnemyID target, float spd, int dmg)
    {
        return ProjectileData{
            ProjectileType::MAGIC,
            pos,
            dmg,
            {}, // Omitted: direction
            spd,
            target};
    }
};

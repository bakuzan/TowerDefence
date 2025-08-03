#pragma once

struct EnemyStats
{
    int health;
    int damage;
    float speed;
    int pointsValue;

    static EnemyStats create(int health, int damage, float speed, int points)
    {
        return {health, damage, speed, points};
    }
};
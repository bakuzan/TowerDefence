#pragma once

struct EnemyStats
{
    int health;
    float speed;
    int pointsValue;

    static EnemyStats create(int health, float speed, int points)
    {
        return {health, speed, points};
    }
};
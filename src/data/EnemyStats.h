#pragma once

struct EnemyStats
{
    int health;
    float speed;

    static EnemyStats Create(int health, float speed)
    {
        return {health, speed};
    }
};
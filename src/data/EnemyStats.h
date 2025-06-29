#pragma once

struct EnemyStats
{
    int health;
    float speed;

    static EnemyStats create(int health, float speed)
    {
        return {health, speed};
    }
};
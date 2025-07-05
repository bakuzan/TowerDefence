#pragma once

struct TowerAttributes
{
    float fireRateCooldown;
    float fireRange;
    float projectileSpeed;
    int projectileDamage;

    static TowerAttributes createRangedAttributes(float cooldown, float range,
                                                  float speed, int damage)
    {
        return {cooldown, range, speed, damage};
    }

    static TowerAttributes createAttributes()
    {
        return {0.0f, 0.0f, 0.0f, 0};
    }
};
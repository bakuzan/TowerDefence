#ifndef PROJECTILESPAWNMANAGER_H
#define PROJECTILESPAWNMANAGER_H

#include <memory>

#include "components/TextureRectManager.h"

#include "constants/ProjectileType.h"
#include "data/ProjectileData.h"
#include "entities/Projectile.h"

class ProjectileSpawnManager
{
private:
    const TextureRectManager &projectileRectManager;

private:
    std::unique_ptr<Projectile> spawnProjectile(
        const sf::Texture &texture,
        const ProjectileData &data);

public:
    ProjectileSpawnManager(const TextureRectManager &textureRectManager);
    ~ProjectileSpawnManager();

    void spawnProjectile(const sf::Texture &texture,
                         std::vector<std::unique_ptr<Projectile>> &projectiles,
                         ProjectileData &data);
};

#endif // PROJECTILESPAWNMANAGER_H
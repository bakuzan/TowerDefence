#include "constants/Constants.h"

#include "ProjectileSpawnManager.h"
#include "entities/ArrowProjectile.h"
#include "entities/MagicProjectile.h"

ProjectileSpawnManager::ProjectileSpawnManager(const TextureRectManager &textureRectManager)
    : projectileRectManager(textureRectManager)
{
    // Constructor
}

ProjectileSpawnManager::~ProjectileSpawnManager()
{
    // Destructor
}

// Publics

void ProjectileSpawnManager::spawnProjectile(
    const sf::Texture &texture,
    std::vector<std::unique_ptr<Projectile>> &projectiles,
    ProjectileData &data)
{
    projectiles.emplace_back(spawnProjectile(texture, data));
}

// Privates

std::unique_ptr<Projectile> ProjectileSpawnManager::spawnProjectile(
    const sf::Texture &texture,
    const ProjectileData &data)
{
    switch (data.type)
    {
    case ProjectileType::ARROW:
        return std::make_unique<ArrowProjectile>(
            data.type,
            texture,
            projectileRectManager.getTextureRect(data.type),
            data.spawnPosition,
            data.speed,
            data.damage,
            data.direction);
    case ProjectileType::MAGIC:
        return std::make_unique<MagicProjectile>(
            data.type,
            texture,
            projectileRectManager.getTextureRect(data.type),
            data.spawnPosition,
            data.speed,
            data.damage,
            data.targetId);
    default:
        throw std::logic_error("Unhandled ProjectileType in ProjectileSpawnManager::spawnProjectile()");
    }
}
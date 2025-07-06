#ifndef MAGICPROJECTILE_H
#define MAGICPROJECTILE_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "constants/Identifiers.h"
#include "constants/ProjectileType.h"
#include "entities/Enemy.h"
#include "entities/Projectile.h"

class MagicProjectile : public Projectile
{
private:
    EnemyID targetEnemyId;

private:
    Enemy *findEnemyById(const std::vector<std::unique_ptr<Enemy>> &enemies,
                         EnemyID id);

public:
    MagicProjectile(ProjectileType type,
                    const sf::Texture &texture, sf::IntRect textureRect,
                    sf::Vector2f spawnPosition,
                    float speed,
                    int damage,
                    EnemyID enemyID);
    ~MagicProjectile() override;

    void update(float deltaTime, const std::vector<std::unique_ptr<Enemy>> &enemies) override;
};

#endif // MAGICPROJECTILE_H

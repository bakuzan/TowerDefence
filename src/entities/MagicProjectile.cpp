#include "MagicProjectile.h"
#include "utils/GameUtils.h"

MagicProjectile::MagicProjectile(ProjectileType type,
                                 const sf::Texture &texture, sf::IntRect textureRect,
                                 sf::Vector2f spawnPosition,
                                 float speed,
                                 int damage,
                                 EnemyID enemyID)
    : Projectile(type,
                 texture, textureRect,
                 spawnPosition,
                 speed,
                 damage),
      targetEnemyId(enemyID)
{
    // Constructor
}

MagicProjectile::~MagicProjectile()
{
    // Destructor
}

// Publics

void MagicProjectile::update(float deltaTime,
                             const std::vector<std::unique_ptr<Enemy>> &enemies)
{
    Enemy *target = findEnemyById(enemies, targetEnemyId);

    if (target != nullptr)
    {
        sf::Vector2f direction = GameUtils::normaliseVector(target->getSprite().getPosition() - sprite.getPosition());
        sprite.move(direction * speed * deltaTime);
    }
    else
    {
        canRemove = true;
    }
}

// Privates

Enemy *MagicProjectile::findEnemyById(const std::vector<std::unique_ptr<Enemy>> &enemies,
                                      EnemyID id)
{
    for (const auto &enemy : enemies)
    {
        if (enemy->getID() == id)
        {
            return enemy.get();
        }
    }

    return nullptr;
}

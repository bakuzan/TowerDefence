#include "constants/Constants.h"
#include "components/TowerAttributesManager.h"
#include "utils/GameUtils.h"

#include "ArcherTower.h"

ArcherTower::ArcherTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
                         sf::Vector2f position)
    : RangedTower(TowerType::ARCHER, texture, textureRects, position)
{
    // Constructor
}

ArcherTower::~ArcherTower()
{
    // Destructor
}

// Publics

void ArcherTower::update(float dt)
{
    updateTextureRect(level - 1, (Constants::TILE_SURFACE_HEIGHT / 4.0f));
}

std::optional<ProjectileData> ArcherTower::getShootData(float deltaTime,
                                                        const std::vector<std::unique_ptr<Enemy>> &enemies)
{
    const auto &attrs = TowerAttributesManager::getInstance().getAttributes(type, level);

    const Enemy *target = tryAcquireTargetAndCooldown(deltaTime,
                                                      attrs.fireRateCooldown,
                                                      attrs.fireRange,
                                                      enemies);

    if (!target)
    {
        return std::nullopt;
    }

    sf::Vector2f spawnPosition = sprite.getPosition() - sf::Vector2f(0, sprite.getLocalBounds().height / 2.0f);
    sf::Vector2f direction = GameUtils::normaliseVector(target->getSprite().getPosition() - sprite.getPosition());

    return ProjectileData::createArrow(
        spawnPosition,
        direction,
        attrs.projectileSpeed,
        attrs.projectileDamage);
}

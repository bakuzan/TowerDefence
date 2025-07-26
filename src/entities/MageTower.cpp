#include "constants/Constants.h"
#include "components/TowerAttributesManager.h"

#include "MageTower.h"

MageTower::MageTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
                     sf::Vector2f position)
    : RangedTower(TowerType::MAGE, texture, textureRects, position)
{
    // Constructor
}

MageTower::~MageTower()
{
    // Destructor
}

// Publics

void MageTower::update(float dt)
{
    (void)dt; // ignore

    updateTextureRect(level - 1, (Constants::TILE_SURFACE_HEIGHT / 3.0f));
}

std::optional<ProjectileData> MageTower::getShootData(float deltaTime,
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

    sf::FloatRect bounds = sprite.getLocalBounds();
    sf::Vector2f spawnPosition = sprite.getPosition() - sf::Vector2f(bounds.width / 4.0f, bounds.height / 4.0f);

    return ProjectileData::createMagic(
        spawnPosition,
        target->getID(),
        attrs.projectileSpeed,
        attrs.projectileDamage);
}

#include "constants/Constants.h"
#include "constants/SoldierType.h"
#include "MeleeTower.h"

MeleeTower::MeleeTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
                       sf::Vector2f position)
    : Tower(TowerType::MELEE, texture, textureRects, position)
{
    int textureIndex = calculateTextureIndex();
    updateTextureRect(textureIndex, (Constants::TILE_SURFACE_HEIGHT / 4.0f));
}

MeleeTower::~MeleeTower()
{
    // Destructor
}

// Publics

void MeleeTower::update(float dt)
{
    (void)dt; // ignored

    int textureIndex = calculateTextureIndex();
    updateTextureRect(textureIndex, (Constants::TILE_SURFACE_HEIGHT / 4.0f));
}

std::optional<SoldierSpawnData> MeleeTower::getSoldierData(float dt)
{
    // If soldier still exists, don't do anything
    if (auto soldierPtr = deployedSoldier.lock())
    {
        if (!soldierPtr->isDead())
        {
            return std::nullopt;
        }
    }

    spawnCooldownTimer += dt;

    if (spawnCooldownTimer < (spawnCooldown / level))
    {
        return std::nullopt;
    }

    spawnCooldownTimer = 0.0f;

    sf::Vector2f spawnPos = sprite.getPosition();
    deployedSoldier.reset();

    int levelIndex = level - 1;
    return SoldierSpawnData::create(static_cast<SoldierType>(levelIndex),
                                    spawnPos,
                                    100 + (levelIndex * 10),
                                    20 + (levelIndex * 5));
}

void MeleeTower::setDeployedSoldier(const std::shared_ptr<Soldier> &soldier)
{
    deployedSoldier = soldier;
}

std::weak_ptr<Soldier> MeleeTower::getSoldier()
{
    return deployedSoldier;
}

// Privates

int MeleeTower::calculateTextureIndex()
{
    return 2 * level - 1;
}
#include "constants/Constants.h"
#include "constants/SoldierType.h"
#include "MeleeTower.h"

MeleeTower::MeleeTower(const sf::Texture &texture, const std::vector<sf::IntRect> &textureRects,
                       sf::Vector2f position)
    : Tower(TowerType::MELEE, texture, textureRects, position)
{
    // Constructor
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
    spawnCooldownTimer += dt;

    // If soldier still exists, don't do anything
    if (auto soldierPtr = deployedSoldier.lock())
    {
        if (!soldierPtr->isDead())
        {
            return std::nullopt;
        }
    }

    if (spawnCooldownTimer < (spawnCooldown / level))
    {
        return std::nullopt;
    }

    spawnCooldownTimer = 0.0f;

    sf::Vector2f spawnPos = sprite.getPosition();
    deployedSoldier.reset();

    return SoldierSpawnData::create(SoldierType::BASIC,
                                    spawnPos,
                                    100,
                                    15, 0.5f);
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
    int levelIndex = level - 1;
    return level + (levelIndex * 2);
}
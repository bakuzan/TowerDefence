#include "TowerAttributesManager.h"

TowerAttributesManager::TowerAttributesManager()
{
    towerStats[TowerType::ARCHER] = {
        TowerAttributes::createRangedAttributes(0.4f, 375.0f, 350.0f, 18),
        TowerAttributes::createRangedAttributes(0.35f, 375.0f, 350.0f, 22),
        TowerAttributes::createRangedAttributes(0.3f, 375.0f, 350.0f, 26)};

    towerStats[TowerType::MAGE] = {
        TowerAttributes::createRangedAttributes(0.8f, 280.0f, 200.0f, 28),
        TowerAttributes::createRangedAttributes(0.6f, 280.0f, 250.0f, 36),
        TowerAttributes::createRangedAttributes(0.4f, 280.0f, 300.0f, 45)};
}

TowerAttributesManager::~TowerAttributesManager()
{
    // Destructor
}

// Publics

const TowerAttributes &TowerAttributesManager::getAttributes(TowerType type, int level) const
{
    return towerStats.at(type).at(level - 1);
}
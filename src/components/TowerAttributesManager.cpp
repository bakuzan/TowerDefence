#include "TowerAttributesManager.h"

TowerAttributesManager::TowerAttributesManager()
{
    towerStats[TowerType::ARCHER] = {
        TowerAttributes::createRangedAttributes(0.33f, 300.0f, 200.0f, 15),
        TowerAttributes::createRangedAttributes(0.29f, 350.0f, 275.0f, 20),
        TowerAttributes::createRangedAttributes(0.25f, 400.0f, 350.0f, 25)};

    towerStats[TowerType::MAGE] = {
        TowerAttributes::createRangedAttributes(0.8f, 200.0f, 125.0f, 30),
        TowerAttributes::createRangedAttributes(0.6f, 200.0f, 175.0f, 40),
        TowerAttributes::createRangedAttributes(0.4f, 200.0f, 225.0f, 50)};
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
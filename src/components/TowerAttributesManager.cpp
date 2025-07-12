#include "TowerAttributesManager.h"

TowerAttributesManager::TowerAttributesManager()
{
    towerStats[TowerType::ARCHER] = {
        TowerAttributes::createRangedAttributes(0.33f, 350.0f, 350.0f, 20),
        TowerAttributes::createRangedAttributes(0.29f, 375.0f, 350.0f, 25),
        TowerAttributes::createRangedAttributes(0.25f, 400.0f, 350.0f, 30)};

    towerStats[TowerType::MAGE] = {
        TowerAttributes::createRangedAttributes(0.8f, 300.0f, 200.0f, 30),
        TowerAttributes::createRangedAttributes(0.6f, 300.0f, 250.0f, 40),
        TowerAttributes::createRangedAttributes(0.4f, 300.0f, 300.0f, 50)};
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
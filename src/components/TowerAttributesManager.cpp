#include "TowerAttributesManager.h"

TowerAttributesManager::TowerAttributesManager()
{
    towerStats[TowerType::ARCHER] = {
        TowerAttributes::createRangedAttributes(0.33f, 575.0f, 120.0f, 20),
        TowerAttributes::createRangedAttributes(0.30f, 575.0f, 150.0f, 27),
        TowerAttributes::createRangedAttributes(0.27f, 575.0f, 180.0f, 34)};

    towerStats[TowerType::MAGE] = {
        TowerAttributes::createRangedAttributes(0.5f, 430.0f, 80.0f, 34),
        TowerAttributes::createRangedAttributes(0.4f, 430.0f, 85.0f, 45),
        TowerAttributes::createRangedAttributes(0.33f, 430.0f, 90.0f, 56)};
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
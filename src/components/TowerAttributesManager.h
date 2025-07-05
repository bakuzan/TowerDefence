
#ifndef TOWERATTRIBUTESMANAGER_H
#define TOWERATTRIBUTESMANAGER_H

#include <array>
#include <unordered_map>

#include "constants/TowerType.h"
#include "data/TowerAttributes.h"

class TowerAttributesManager
{
private:
    std::unordered_map<TowerType, std::array<TowerAttributes, 3>> towerStats;

private:
    TowerAttributesManager();
    ~TowerAttributesManager();

public:
    static TowerAttributesManager &getInstance()
    {
        static TowerAttributesManager instance;
        return instance;
    }

    const TowerAttributes &getAttributes(TowerType type, int level) const;
};

#endif // TOWERATTRIBUTESMANAGER_H

#ifndef TOWER_H
#define TOWER_H

#include "constants/TowerType.h"

class Tower
{
protected:
    TowerType type;
    int level;

public:
    Tower(TowerType towerType);
    ~Tower();

    const int getLevel() const;
    const TowerType getType() const;

    void levelUp();
};

#endif // TOWER_H

#ifndef ARCHERTOWER_H
#define ARCHERTOWER_H

#include "Tower.h"

class ArcherTower : public Tower
{
public:
    ArcherTower();
    ~ArcherTower();

    void update(float dt) override;
};

#endif // ARCHERTOWER_H

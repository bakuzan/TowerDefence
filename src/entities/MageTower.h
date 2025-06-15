#ifndef MAGETOWER_H
#define MAGETOWER_H

#include "Tower.h"

class MageTower : public Tower
{
public:
    MageTower();
    ~MageTower();

    void update(float dt) override;
};

#endif // MAGETOWER_H

#ifndef MELEETOWER_H
#define MELEETOWER_H

#include "Tower.h"

class MeleeTower : public Tower
{
public:
    MeleeTower();
    ~MeleeTower();

    void update(float dt) override;
};

#endif // MELEETOWER_H

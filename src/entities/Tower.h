#ifndef TOWER_H
#define TOWER_H

#include <SFML/Graphics.hpp>

#include "constants/TowerType.h"

class Tower
{
protected:
    TowerType type;
    int level;

    sf::Sprite sprite;

public:
    Tower(TowerType towerType);
    ~Tower();

    virtual void update(float dt) = 0;
    void render(sf::RenderWindow &window) const;

    const int getLevel() const;
    const TowerType getType() const;

    void levelUp();
};

#endif // TOWER_H

#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "constants/TowerType.h"
#include "entities/Tower.h"
#include "entities/MeleeTower.h"
#include "entities/ArcherTower.h"
#include "entities/MageTower.h"

struct TowerSpot
{
    std::unique_ptr<Tower> tower = nullptr;

    bool hasTower() const
    {
        return tower != nullptr;
    }

    bool isUpgradeable() const
    {
        return tower && tower->getLevel() < 3;
    }

    void placeTower(TowerType type,
                    const sf::Texture &texture,
                    const std::vector<sf::IntRect> &textureRects,
                    sf::Vector2f position)
    {
        switch (type)
        {
        case TowerType::MELEE:
            tower = std::make_unique<MeleeTower>(texture, textureRects, position);
            break;
        case TowerType::ARCHER:
            tower = std::make_unique<ArcherTower>(texture, textureRects, position);
            break;
        case TowerType::MAGE:
            tower = std::make_unique<MageTower>(texture, textureRects, position);
            break;
        }
    }

    void removeTower()
    {
        tower.reset();
    }
};
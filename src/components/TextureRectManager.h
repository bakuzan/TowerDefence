#ifndef TEXTURERECTMANAGER_H
#define TEXTURERECTMANAGER_H

#include <SFML/Graphics.hpp>

#include <unordered_map>

#include "constants/TowerType.h"

class TextureRectManager
{
private:
    std::unordered_map<TowerType, std::vector<sf::IntRect>> towerTextureRects;

private:
    void initTowerTextureRects();

public:
    TextureRectManager();
    ~TextureRectManager();

    const sf::IntRect &getTextureRect(TowerType type, int position = 0) const;
};

#endif // TEXTURERECTMANAGER_H

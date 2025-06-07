#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <SFML/Graphics.hpp>

#include <unordered_map>

#include "TextureManager.h"
#include "AudioManager.h"
#include "data/TowerSpot.h"
#include "utils/HashUtilities.h"

class GameData
{
private:
    std::unordered_map<sf::Vector2i, TowerSpot> towerSpots;

public:
    sf::Font gameFont;

    TextureManager textureManager;
    AudioManager audioManager;

public:
    GameData();
    ~GameData();

    std::unordered_map<sf::Vector2i, TowerSpot> &getTowerSpots();

    void reset();
};

#endif // GAMEDATA_H

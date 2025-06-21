#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <SFML/Graphics.hpp>

#include <unordered_map>

#include "TextureManager.h"
#include "AudioManager.h"
#include "components/TextureRectManager.h"
#include "data/TowerSpot.h"
#include "utils/HashUtilities.h"

class GameData
{
private:
    std::unordered_map<sf::Vector2i, TowerSpot> towerSpots;
    int playerGold;
    int playerLives;
    int playerScore;

public:
    sf::Font gameFont;

    TextureManager textureManager;
    AudioManager audioManager;

    TextureRectManager rectManager;

public:
    GameData();
    ~GameData();

    std::unordered_map<sf::Vector2i, TowerSpot> &getTowerSpots();

    const int getPlayerGold() const;
    void updatePlayerGold(int adjustment);

    const int getPlayerLives() const;
    void updatePlayerLives(int adjustment);

    const int getPlayerScore() const;
    void updatePlayerScore(int adjustment);

    void reset();
};

#endif // GAMEDATA_H

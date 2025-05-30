#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <SFML/Graphics.hpp>

#include "TextureManager.h"
#include "AudioManager.h"

class GameData
{
public:
    sf::Font gameFont;

    TextureManager textureManager;
    AudioManager audioManager;

public:
    GameData();
    ~GameData();

    void reset();
};

#endif // GAMEDATA_H

#include "GameData.h"
#include "constants/Constants.h"

GameData::GameData()
{
    // Load textures
    // TODO

    // Load audio
    // TODO

    // Load font
    if (!gameFont.loadFromFile("resources/fonts/PressStart2P-Regular.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }

    reset();
}

GameData::~GameData()
{
    // Destructor
}

// Publics

void GameData::reset()
{
}
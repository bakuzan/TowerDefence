#include <fstream>
#include <sstream>

#include "TileMap.h"

TileMap::TileMap(const sf::Texture &atlas,
                 int mWidth, int mHeight,
                 int tWidth, int tHeight)
    : textureAtlas(atlas),
      mapWidth(mWidth), mapHeight(mHeight),
      tileWidth(tWidth), tileHeight(tHeight)
{
    mapData.resize(mHeight, std::vector<TileId>(mWidth, TileId::TERRAIN)); // Initialize empty map
}

TileMap::~TileMap()
{
    // Destructor
}

// Publics

void TileMap::loadMapFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;
    int rowIndex = 0;

    while (std::getline(file, line) &&
           rowIndex < mapHeight)
    {
        std::stringstream ss(line);
        int tileValue;

        for (int colIndex = 0; colIndex < mapWidth && ss >> tileValue; ++colIndex)
        {
            mapData[rowIndex][colIndex] = static_cast<TileId>(tileValue);

            if (ss.peek() == ',')
            {
                ss.ignore();
            }
        }

        ++rowIndex;
    }
}

void TileMap::render(sf::RenderWindow &window)
{
    for (int y = 0; y < mapHeight; ++y)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            TileId tileId = mapData[y][x];

            sf::Sprite sprite;
            sprite.setTexture(textureAtlas);
            sprite.setTextureRect(getTileRect(tileId, x, y));
            sprite.setPosition(gridToIso(x, y, tileWidth, tileHeight));
            window.draw(sprite);
        }
    }
}

sf::Vector2f TileMap::getCentre()
{
    return gridToIso(mapWidth / 2, mapHeight / 2, tileWidth, tileHeight);
}

// Privates

sf::IntRect TileMap::getTileRect(TileId tileId, int x, int y)
{
    int id = static_cast<int>(tileId);

    if (tileId == TileId::PATH)
    {
        id = 2 + static_cast<int>(resolvePathType(x, y));
    }

    return sf::IntRect(id * tileWidth, 0, tileWidth, tileHeight);
}

sf::Vector2f TileMap::gridToIso(int x, int y, int tileWidth, int tileHeight)
{
    float screenX = (x - y) * (tileWidth / 2);
    float screenY = (x + y) * (tileHeight * 0.3f);
    return {screenX, screenY};
}

PathType TileMap::resolvePathType(int x, int y)
{
    bool left = (x > 0) && (mapData[y][x - 1] == TileId::PATH);
    bool right = (x < mapData[y].size() - 1) && (mapData[y][x + 1] == TileId::PATH);
    bool up = (y > 0) && (mapData[y - 1][x] == TileId::PATH);
    bool down = (y < mapData.size() - 1) && (mapData[y + 1][x] == TileId::PATH);

    // Cross
    if (left && right && up && down)
    {
        return PathType::CROSSROAD;
    }

    // T's
    if (left && right && up)
    {
        return PathType::T_DOWNWARDS;
    }
    if (left && right && down)
    {
        return PathType::T_UPWARDS;
    }
    if (up && down && left)
    {
        return PathType::T_RIGHT;
    }
    if (up && down && right)
    {
        return PathType::T_LEFT;
    }

    // Corners
    if (left && down)
    {
        return PathType::CORNER_TOP_RIGHT;
    }
    if (right && down)
    {
        return PathType::CORNER_TOP_LEFT;
    }
    if (left && up)
    {
        return PathType::CORNER_BOTTOM_RIGHT;
    }
    if (right && up)
    {
        return PathType::CORNER_BOTTOM_LEFT;
    }

    // Straights
    if (left && right)
    {
        return PathType::STRAIGHT_HORIZONTAL;
    }
    if (up && down)
    {
        return PathType::STRAIGHT_VERTICAL;
    }

    return PathType::STRAIGHT_HORIZONTAL; // Random default...
}

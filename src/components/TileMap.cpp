#include <fstream>

#include "TileMap.h"

TileMap::TileMap(const sf::Texture &atlas,
                 int mWidth, int mHeight,
                 int tWidth, int tHeight)
    : textureAtlas(atlas),
      mapWidth(mWidth), mapHeight(mHeight),
      tileWidth(tWidth), tileHeight(tHeight)
{
    mapData.resize(mHeight, std::vector<int>(mWidth, TileId::Grass)); // Initialize empty map
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

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::vector<TileId> tileRow;
        int tileValue;

        while (ss >> tileValue)
        {
            tileRow.push_back(static_cast<TileId>(tileValue));

            if (ss.peek() == ',')
            {
                ss.ignore();
            }
        }

        mapData.push_back(tileRow);
    }
}

void TileMap::render(sf::RenderWindow &window)
{
    for (size_t y = 0; y < mapData.size(); ++y)
    {
        for (size_t x = 0; x < mapData[y].size(); ++x)
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

// Privates

sf::IntRect TileMap::getTileRect(TileId tileId, int x, int y)
{
    int id = static_cast<int>(tileId);

    if (tileId == TileId::Path)
    {
        id = 2 + static_cast<int>(resolvePathType(x, y));
    }

    return sf::IntRect(id * tileWidth, 0, tileWidth, tileHeight);
}

sf::Vector2f TileMap::gridToIso(int x, int y, int tileWidth, int tileHeight)
{
    float screenX = (x - y) * (tileWidth / 2);
    float screenY = (x + y) * (tileHeight / 2);
    return {screenX, screenY};
}

PathType TileMap::resolvePathType(int x, int y)
{
    bool left = (x > 0) && (mapData[y][x - 1] == TileId::Path);
    bool right = (x < mapData[y].size() - 1) && (mapData[y][x + 1] == TileId::Path);
    bool up = (y > 0) && (mapData[y - 1][x] == TileId::Path);
    bool down = (y < mapData.size() - 1) && (mapData[y + 1][x] == TileId::Path);

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

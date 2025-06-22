#include <fstream>
#include <sstream>

#include "constants/Constants.h"
#include "TileMap.h"

TileMap::TileMap(const sf::Texture &atlas,
                 int mWidth, int mHeight)
    : textureAtlas(atlas),
      mapWidth(mWidth), mapHeight(mHeight),
      tileWidth(Constants::TILE_WIDTH), tileHeight(Constants::TILE_HEIGHT),
      surfaceHeight(Constants::TILE_SURFACE_HEIGHT)
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
    towerSpots.clear();

    while (std::getline(file, line) &&
           rowIndex < mapHeight)
    {
        std::stringstream ss(line);
        int tileValue;

        for (int colIndex = 0; colIndex < mapWidth && ss >> tileValue; ++colIndex)
        {
            TileId tileId = static_cast<TileId>(tileValue);
            mapData[rowIndex][colIndex] = tileId;

            extractImportantTileIndexes(tileId, colIndex, rowIndex);

            if (ss.peek() == ',')
            {
                ss.ignore();
            }
        }

        ++rowIndex;
    }

    // Setup spawnPoints from entrancePoints
    spawnPoints.clear();
    for (const auto &tile : entranceSpots)
    {
        sf::Vector2f spawnPoint = tileIndexToIsoPoint(tile.x, tile.y);
        spawnPoint.x -= tileWidth / 4;
        spawnPoint.y += surfaceHeight / 4;
        spawnPoints.push_back(spawnPoint);
    }
}

void TileMap::render(sf::RenderWindow &window,
                     const std::unordered_map<sf::Vector2i, TowerSpot> &activetowerSpots)
{
    sf::Sprite sprite;
    sprite.setTexture(textureAtlas);

    for (int y = 0; y < mapHeight; ++y)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            TileId tileId = mapData[y][x];
            sf::Vector2i tileIndex(x, y);

            if (activetowerSpots.contains(tileIndex))
            {
                tileId = activetowerSpots.at(tileIndex).hasTower()
                             ? TileId::TERRAIN
                             : TileId::TOWER_SPOT;
            }

            sprite.setTextureRect(getTileRect(tileId, x, y));
            sprite.setOrigin(tileWidth / 2, 0);
            sprite.setPosition(tileIndexToIsoPoint(x, y));
            window.draw(sprite);
        }
    }
}

sf::Vector2f TileMap::getCentre()
{
    return tileIndexToIsoPoint(mapWidth / 2, mapHeight / 2);
}

const std::vector<sf::Vector2i> &TileMap::getTowerSpots() const
{
    return towerSpots;
}

const std::vector<sf::Vector2i> &TileMap::getEntranceSpots() const
{
    return entranceSpots;
}

const std::vector<sf::Vector2f> &TileMap::getSpawnPoints() const
{
    return spawnPoints;
}

const sf::Vector2i &TileMap::getExitSpot() const
{
    return exitSpot;
}

sf::Vector2f TileMap::tileIndexToIsoPoint(int x, int y)
{
    float screenX = (x - y) * (tileWidth / 2);
    float screenY = (x + y) * (surfaceHeight / 2);
    return {screenX, screenY};
}

sf::Vector2i TileMap::isoPointToTileIndex(const sf::Vector2f &mousePos)
{
    float tileWidthAdjusted = tileWidth / 2;
    float tileHeightAdjusted = surfaceHeight / 2;

    float worldX = ((mousePos.x / tileWidthAdjusted) + (mousePos.y / tileHeightAdjusted)) / 2;
    float worldY = ((mousePos.y / tileHeightAdjusted) - (mousePos.x / tileWidthAdjusted)) / 2;

    return {static_cast<int>(worldX), static_cast<int>(worldY)};
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

PathType TileMap::resolvePathType(int x, int y)
{
    int maxY = mapData.size() - 1;
    int maxX = mapData[y].size() - 1;

    bool left = (y < maxY) && (mapData[y + 1][x] == TileId::PATH);
    bool right = (y > 0) && (mapData[y - 1][x] == TileId::PATH);
    bool down = (x < maxX) && (mapData[y][x + 1] == TileId::PATH);
    bool up = (x > 0) && (mapData[y][x - 1] == TileId::PATH);

    // Cross
    if (left && right && up && down)
    {
        return PathType::CROSSROAD;
    }

    // T's
    if (left && right && up)
    {
        return PathType::T_UPWARDS;
    }
    if (left && right && down)
    {
        return PathType::T_DOWNWARDS;
    }
    if (up && down && left)
    {
        return PathType::T_LEFT;
    }
    if (up && down && right)
    {
        return PathType::T_RIGHT;
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
    if ((left || right) && !up && !down)
    {
        return PathType::STRAIGHT_HORIZONTAL;
    }
    if ((up || down) && !left && !right)
    {
        return PathType::STRAIGHT_VERTICAL;
    }

    return PathType::STRAIGHT_HORIZONTAL; // Random default...
}

void TileMap::extractImportantTileIndexes(TileId tileId,
                                          int colIndex,
                                          int rowIndex)
{
    if (tileId == TileId::TOWER_SPOT)
    {
        towerSpots.push_back({colIndex, rowIndex});
    }
    else if (tileId == TileId::PATH &&
             colIndex == 0)
    {
        entranceSpots.push_back({colIndex, rowIndex});
    }
    else if (tileId == TileId::PATH &&
             colIndex == mapWidth - 1)
    {
        exitSpot = sf::Vector2i(colIndex, rowIndex);
    }
}
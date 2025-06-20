#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>
#include <vector>

#include "constants/TileId.h"
#include "constants/PathType.h"
#include "data/TowerSpot.h"
#include "utils/HashUtilities.h"

class TileMap
{
private:
    const sf::Texture &textureAtlas;
    std::vector<std::vector<TileId>> mapData;
    std::vector<sf::Vector2i> towerSpots;
    std::vector<sf::Vector2i> entranceSpots;
    sf::Vector2i exitSpot;

    int mapWidth, mapHeight;
    int tileWidth, tileHeight;
    int surfaceHeight;

private:
    sf::IntRect getTileRect(TileId tileId, int x, int y);
    PathType resolvePathType(int x, int y);
    void extractImportantTileIndexes(TileId tileId, int colIndex, int rowIndex);

public:
    TileMap(const sf::Texture &atlas,
            int mWidth, int mHeight);
    ~TileMap();

    void loadMapFromFile(const std::string &filename);
    void render(sf::RenderWindow &window,
                const std::unordered_map<sf::Vector2i, TowerSpot> &activetowerSpots);

    sf::Vector2f getCentre();
    const std::vector<sf::Vector2i> &getTowerSpots() const;
    const std::vector<sf::Vector2i> &getEntranceSpots() const;
    const sf::Vector2i &getExitSpot() const;

    sf::Vector2f tileIndexToIsoPoint(int x, int y);
    sf::Vector2i isoPointToTileIndex(const sf::Vector2f &mousePos);
};

#endif // TILEMAP_H

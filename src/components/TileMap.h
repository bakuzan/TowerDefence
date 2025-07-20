#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <unordered_map>
#include <vector>

#include "constants/TileId.h"
#include "constants/PathType.h"
#include "data/TowerSpot.h"
#include "utils/HashUtilities.h"
#include "utils/OrderingUtilities.h"
#include "utils/PathingTypes.h"

class TileMap
{
private:
    const sf::Texture &textureAtlas;
    std::vector<std::vector<TileId>> mapData;
    std::vector<sf::Vector2i> towerSpots;
    std::vector<sf::Vector2i> entranceSpots;
    sf::Vector2i exitSpot;

    std::map<sf::Vector2i, sf::Vector2i, Vector2Comparator<int>> flowField;
    PathMap mapPaths;

    int mapWidth, mapHeight;
    int tileWidth, tileHeight;
    int surfaceHeight;

private:
    sf::IntRect getTileRect(TileId tileId, int row, int x, int y);
    PathType resolvePathType(int x, int y);
    void extractImportantTileIndexes(TileId tileId, int colIndex, int rowIndex);

    void buildFlowField();
    std::vector<sf::Vector2i> reconstructPathFromFlow(sf::Vector2i startTileIndex,
                                                      sf::Vector2i endTileIndex);
    bool isInBounds(sf::Vector2i tile) const;
    bool isWalkable(sf::Vector2i tile) const;

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
    const PathMap &getMapPaths() const;

    sf::Vector2f tileIndexToIsoPoint(int x, int y);
    sf::Vector2i isoPointToTileIndex(const sf::Vector2f &isoPoint);
};

#endif // TILEMAP_H

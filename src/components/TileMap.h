#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>
#include <vector>

#include "constants/TileId.h"
#include "constants/PathType.h"

class TileMap
{
private:
    const sf::Texture &textureAtlas;
    std::vector<std::vector<TileId>> mapData;
    std::vector<sf::Vector2i> towerSpots;

    int mapWidth, mapHeight;
    int tileWidth, tileHeight;

private:
    sf::IntRect getTileRect(TileId tileId, int x, int y);
    sf::Vector2f gridToIso(int x, int y, int tileWidth, int tileHeight);
    PathType resolvePathType(int x, int y);

public:
    TileMap(const sf::Texture &atlas,
            int mWidth, int mHeight,
            int tWidth, int tHeight);
    ~TileMap();

    void loadMapFromFile(const std::string &filename);
    void render(sf::RenderWindow &window);

    sf::Vector2f getCentre();
    const std::vector<sf::Vector2i> &getTowerSpots() const;

    sf::Vector2i getIsometricTileIndex(const sf::Vector2f &mousePos);
};

#endif // TILEMAP_H

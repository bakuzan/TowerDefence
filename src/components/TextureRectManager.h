#ifndef TEXTURERECTMANAGER_H
#define TEXTURERECTMANAGER_H

#include <SFML/Graphics.hpp>

#include <unordered_map>

#include "constants/EnemyType.h"
#include "constants/TowerType.h"
#include "constants/ProjectileType.h"
#include "constants/IconType.h"

class TextureRectManager
{
private:
    std::unordered_map<TowerType, std::vector<sf::IntRect>> towerTextureRects;
    std::unordered_map<EnemyType, sf::IntRect> enemyTextureRects;
    std::unordered_map<ProjectileType, sf::IntRect> projectileTextureRects;
    std::unordered_map<IconType, sf::IntRect> iconTextureRects;

private:
    void initTowerTextureRects();
    void initEnemyTextureRects();
    void initProjectileTextureRects();
    void initIconTextureRects();

public:
    TextureRectManager();
    ~TextureRectManager();

    const sf::IntRect &getTextureRect(TowerType type, int position = 0) const;
    const std::vector<sf::IntRect> &getTextureRects(TowerType type) const;

    const sf::IntRect &getTextureRect(EnemyType type) const;
    const sf::IntRect &getTextureRect(ProjectileType type) const;
    const sf::IntRect &getTextureRect(IconType type) const;
};

#endif // TEXTURERECTMANAGER_H

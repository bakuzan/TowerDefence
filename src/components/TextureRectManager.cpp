#include "TextureRectManager.h"

TextureRectManager::TextureRectManager()
{
    initTowerTextureRects();
    initEnemyTextureRects();
    initProjectileTextureRects();
}

TextureRectManager::~TextureRectManager()
{
    // Destructor
}

// Publics

const sf::IntRect &TextureRectManager::getTextureRect(TowerType type, int position) const
{
    return getTextureRects(type)[position];
}

const std::vector<sf::IntRect> &TextureRectManager::getTextureRects(TowerType type) const
{
    return towerTextureRects.at(type);
}

const sf::IntRect &TextureRectManager::getTextureRect(EnemyType type) const
{
    return enemyTextureRects.at(type);
}

const sf::IntRect &TextureRectManager::getTextureRect(ProjectileType type) const
{
    return projectileTextureRects.at(type);
}

// Privates

void TextureRectManager::initTowerTextureRects()
{
    towerTextureRects[TowerType::MELEE] = {
        {0, 0, 142, 154}, {154, 0, 142, 154}, {284, 0, 142, 154}, {426, 0, 142, 154}, {568, 0, 142, 154}, {710, 0, 142, 154}};

    towerTextureRects[TowerType::ARCHER] = {
        {0, 154, 130, 165},
        {130, 154, 130, 174},
        {260, 154, 130, 179}};

    towerTextureRects[TowerType::MAGE] = {
        {0, 333, 150, 120},
        {150, 333, 149, 120},
        {299, 333, 135, 120}};
}

void TextureRectManager::initEnemyTextureRects()
{
    enemyTextureRects[EnemyType::BASIC] = {0, 0, 64, 80};
}

void TextureRectManager::initProjectileTextureRects()
{
    projectileTextureRects[ProjectileType::ARROW] = {0, 0, 21, 35};
    projectileTextureRects[ProjectileType::MAGIC] = {21, 11, 14, 15};
}
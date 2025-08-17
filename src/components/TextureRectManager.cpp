#include "TextureRectManager.h"

TextureRectManager::TextureRectManager()
{
    initTowerTextureRects();
    initEnemyTextureRects();
    initProjectileTextureRects();
    initIconTextureRects();
    initSoldierTextureRects();
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

const sf::IntRect &TextureRectManager::getTextureRect(IconType type) const
{
    return iconTextureRects.at(type);
}

const sf::IntRect &TextureRectManager::getTextureRect(SoldierType type) const
{
    return soldierTextureRects.at(type);
}

// Privates

void TextureRectManager::initTowerTextureRects()
{
    towerTextureRects[TowerType::MELEE] = {
        {1, 0, 140, 154}, {143, 0, 140, 154}, {285, 0, 140, 154}, {426, 0, 140, 154}, {568, 0, 140, 154}, {710, 0, 140, 154}};

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
    enemyTextureRects[EnemyType::FAST] = {128, 0, 64, 80};
    enemyTextureRects[EnemyType::TANK] = {384, 0, 64, 80};
}

void TextureRectManager::initProjectileTextureRects()
{
    projectileTextureRects[ProjectileType::ARROW] = {0, 0, 21, 35};
    projectileTextureRects[ProjectileType::MAGIC] = {21, 11, 14, 15};
}

void TextureRectManager::initIconTextureRects()
{
    iconTextureRects[IconType::COIN] = {5, 3, 23, 36};
    iconTextureRects[IconType::HEART] = {35, 3, 36, 35};
}

void TextureRectManager::initSoldierTextureRects()
{
    soldierTextureRects[SoldierType::BASIC] = {0, 0, 37, 53};
    soldierTextureRects[SoldierType::SWORD] = {38, 0, 58, 53};
    soldierTextureRects[SoldierType::SWORD_AND_SHIELD] = {97, 0, 70, 53};
}
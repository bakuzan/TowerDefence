#include "TextureRectManager.h"

TextureRectManager::TextureRectManager()
{
    initTowerTextureRects();
}

TextureRectManager::~TextureRectManager()
{
    // Destructor
}

// Publics

const sf::IntRect &TextureRectManager::getTextureRect(TowerType type, int position) const
{
    return towerTextureRects.at(type)[position];
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
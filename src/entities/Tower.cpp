#include "Tower.h"

Tower::Tower(TowerType towerType,
             const sf::Texture &texture, const std::vector<sf::IntRect> &rects,
             sf::Vector2f position)
    : textureRects(rects),
      type(towerType), level(1),
      tileOriginPosition(position)
{
    sprite.setTexture(texture);
}

Tower::~Tower()
{
    // Destructor
}

// Publics

void Tower::render(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

const int Tower::getLevel() const
{
    return level;
}

const TowerType Tower::getType() const
{
    return type;
}

void Tower::levelUp()
{
    ++level;
}

// Privates

void Tower::updateTextureRect(int textureIndex, float verticalOffset)
{
    if (textureIndex < textureRects.size())
    {
        sf::IntRect rect = textureRects[textureIndex];
        sprite.setTextureRect(rect);
        sprite.setOrigin(rect.width / 2.0f, rect.height / 2.0f);
        sprite.setPosition(tileOriginPosition.x,
                           tileOriginPosition.y + verticalOffset);
    }
}
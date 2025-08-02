#include <cmath>

#include "Soldier.h"

Soldier::Soldier(const sf::Texture &texture, const sf::IntRect &textureRect,
                 sf::Vector2f spawnPosition, sf::Vector2f targetPosition,
                 int soldierHealth,
                 int soldierAttackDamage, float soldierAttackSpeed)
    : health(soldierHealth),
      attackDamage(soldierAttackDamage),
      attackSpeed(soldierAttackSpeed),
      target(targetPosition.x,
             targetPosition.y - (textureRect.height / 4.0f))
{
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    sprite.setOrigin(textureRect.width / 2.0f, textureRect.height / 2.0f);
    sprite.setPosition(spawnPosition.x + (textureRect.width / 2.0f),
                       spawnPosition.y + (textureRect.height / 2.0f));
}

Soldier::~Soldier()
{
    // Destructor
}

// Publics

void Soldier::update(float dt)
{
    sf::Vector2f currentPos = sprite.getPosition();
    sf::Vector2f direction = target - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 1.f)
    {
        sprite.setPosition(target); // Snap to target cleanly
        return;
    }

    // Normalize direction
    sf::Vector2f normalized = direction / distance;
    sf::Vector2f movement = normalized * (distance / moveDuration) * dt;

    sprite.move(movement);
}

void Soldier::render(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

bool Soldier::isDead() const
{
    return health <= 0;
}

#include <cmath>

#include "Soldier.h"

Soldier::Soldier(const sf::Texture &texture, const sf::IntRect &textureRect,
                 sf::Vector2f spawnPosition, sf::Vector2f targetPosition,
                 int soldierHealth,
                 int soldierAttackDamage)
    : health(soldierHealth),
      attackDamage(soldierAttackDamage),
      target(targetPosition.x,
             targetPosition.y - (textureRect.height / 4.0f)),
      damageFeedbackTimer(0.0f)
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

    // Visual feedback for taking damage
    if (damageFeedbackTimer > 0.0f)
    {
        damageFeedbackTimer -= dt;
        sprite.setColor(sf::Color(240, 61, 61)); // Red tint
    }
    else
    {
        sprite.setColor(sf::Color(255, 255, 255)); // Normal
    }
}

void Soldier::render(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

const sf::Sprite &Soldier::getSprite() const
{
    return sprite;
}

sf::Sprite &Soldier::getSprite()
{
    return sprite;
}

int Soldier::getHealth() const
{
    return health;
}

int Soldier::getDamageInflicts() const
{
    return attackDamage;
}

void Soldier::applyDamage(int adjustment)
{
    health = std::max(0, health - adjustment);
    damageFeedbackTimer = damageFlashDuration;
}

bool Soldier::isDead() const
{
    return health <= 0;
}

#ifndef SOLDIER_H
#define SOLDIER_H

#include <SFML/Graphics.hpp>

class Soldier
{
private:
    sf::Sprite sprite;
    int health;
    int attackDamage;
    float attackSpeed;

    sf::Vector2f target;

    float damageFeedbackTimer;
    static constexpr float damageFlashDuration = 0.1f;
    static constexpr float moveDuration = 1.0f;

public:
    Soldier(const sf::Texture &texture, const sf::IntRect &textureRect,
            sf::Vector2f spawnPosition, sf::Vector2f targetPosition,
            int soldierHealth,
            int soldierAttackDamage, float soldierAttackSpeed);
    ~Soldier();

    void update(float dt);
    void render(sf::RenderWindow &window) const;

    const sf::Sprite &getSprite() const;
    sf::Sprite &getSprite();

    int getHealth() const;
    int getDamageInflicts() const;
    void applyDamage(int adjustment);

    bool isDead() const;
};

#endif // SOLDIER_H

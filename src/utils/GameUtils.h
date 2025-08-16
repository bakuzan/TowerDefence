#ifndef GAMEUTILS_H
#define GAMEUTILS_H

#include <SFML/Graphics.hpp>

#include "constants/AudioId.h"
#include "constants/ProjectileType.h"

namespace GameUtils
{
    std::string padNumberAsText(int value, int width, char padChar);
    std::string formatScoreText(int score);
    sf::Vector2f getBottomRightPosition(const sf::RenderWindow &window,
                                        sf::Vector2f elementSize,
                                        float margin = 10.0f);

    sf::Vector2f normaliseVector(const sf::Vector2f &vector);
    float calculateEuclideanDistance(const sf::Vector2f &a,
                                     const sf::Vector2f &b);

    const AudioId getFiredAudioIdForProjectileType(ProjectileType projectileType);
    const AudioId getHitAudioIdForProjectileType(ProjectileType projectileType);
};

#endif // GAMEUTILS_H

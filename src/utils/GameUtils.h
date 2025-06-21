#ifndef GAMEUTILS_H
#define GAMEUTILS_H

#include <SFML/Graphics.hpp>

namespace GameUtils
{
    std::string padNumberAsText(int value, int width, char padChar);
    std::string formatScoreText(int score);
    sf::Vector2f getBottomRightPosition(sf::RenderWindow &window,
                                        sf::Vector2f elementSize,
                                        float margin = 10.0f);
};

#endif // GAMEUTILS_H

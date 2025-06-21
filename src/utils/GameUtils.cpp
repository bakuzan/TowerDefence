#include <cmath>
#include <iomanip>
#include <sstream>

#include "GameUtils.h"

namespace GameUtils
{
    std::string padNumberAsText(int value, int width, char padChar)
    {
        std::stringstream ss;
        ss << std::setw(width) << std::setfill(padChar) << value;
        return ss.str();
    }

    std::string formatScoreText(int score)
    {
        return padNumberAsText(score, 8, '0');
    }

    sf::Vector2f getBottomRightPosition(sf::RenderWindow &window,
                                        sf::Vector2f elementSize,
                                        float margin)
    {
        sf::Vector2f viewSize = window.getDefaultView().getSize();

        return {viewSize.x - elementSize.x - margin,
                viewSize.y - elementSize.y - margin};
    }

}
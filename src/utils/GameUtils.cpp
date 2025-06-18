#include <cmath>
#include <iomanip>
#include <sstream>

#include "constants/Constants.h"
#include "GameUtils.h"

namespace GameUtils
{
    std::string formatScoreText(int score)
    {
        std::stringstream ss;
        ss << std::setw(8) << std::setfill('0') << score;
        return ss.str();
    }

    sf::Vector2f getBottomRightPosition(sf::RenderWindow &window,
                                        float margin)
    {
        sf::Vector2f viewSize = window.getDefaultView().getSize();
        sf::Vector2f buttonSize(Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT);

        return {viewSize.x - buttonSize.x - margin,
                viewSize.y - buttonSize.y - margin};
    }

}
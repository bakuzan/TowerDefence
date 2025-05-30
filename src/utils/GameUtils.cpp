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

}
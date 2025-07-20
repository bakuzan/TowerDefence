#pragma once

#include <SFML/Graphics.hpp>

#include "constants/EnvironmentType.h"

struct EnvironmentOption
{
    EnvironmentType type;
    sf::RectangleShape box;
    sf::Text label;
};

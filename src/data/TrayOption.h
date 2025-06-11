#pragma once

#include <SFML/Graphics.hpp>

#include <string>

struct TrayOption
{
    const sf::Texture &texture;
    sf::IntRect textureRect;
    std::string name;
    int optionId;

    static TrayOption Create(const sf::Texture &texture, sf::IntRect textureRect,
                             std::string name, int optionId)
    {
        return {texture, textureRect, name, optionId};
    }
};
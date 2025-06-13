#pragma once

#include <SFML/Graphics.hpp>

#include <string>

struct TrayOption
{
    const sf::Texture &texture;
    sf::IntRect textureRect;
    std::string name;
    int cost;
    int optionId;

    std::function<void(int optionId)> onSelected;

    static TrayOption Create(const sf::Texture &texture, sf::IntRect textureRect,
                             std::string name, int cost, int optionId,
                             std::function<void(int optionId)> selectionCallback)
    {
        return {texture, textureRect, name, cost, optionId, selectionCallback};
    }
};
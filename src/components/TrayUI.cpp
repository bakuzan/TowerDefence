#include <iostream>

#include "TrayUI.h"

TrayUI::TrayUI(sf::RenderWindow *windowRef, sf::Vector2f pos, sf::Vector2f size)
    : window(windowRef), position(pos), isVisible(false)
{
    background.setSize(size);
    background.setPosition(pos);
    background.setFillColor(sf::Color(84, 98, 111, 200));
}

TrayUI::~TrayUI()
{
    // Destructor
}

// Publics

void TrayUI::handleInput(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePixelPos(event.mouseButton.x, event.mouseButton.y);
        sf::Vector2f mouseWorldPos = window->mapPixelToCoords(mousePixelPos, window->getDefaultView());

        for (size_t i = 0; i < optionIcons.size(); ++i)
        {
            if (optionIcons[i].getGlobalBounds().contains(mouseWorldPos) &&
                onOptionSelectedCallback)
            {
                onOptionSelectedCallback(options[i]);
            }
        }
    }
}

void TrayUI::render(sf::RenderWindow &window)
{
    if (!isVisible)
    {
        return;
    }

    window.draw(background);

    for (auto &icon : optionIcons)
    {
        window.draw(icon);
    }
}

void TrayUI::addOption(TrayOption option)
{
    sf::Sprite icon;
    icon.setTexture(option.texture);
    icon.setTextureRect(option.textureRect);

    float verticalOffset = 0.0f;
    for (const auto &prevIcon : optionIcons)
    {
        verticalOffset += prevIcon.getTextureRect().height + 25.0f;
    }

    icon.setPosition(position + sf::Vector2f(0, verticalOffset));
    // TODO
    // Show cost of option
    options.push_back(option);
    optionIcons.push_back(icon);
}

void TrayUI::setOnOptionSelectedCallback(std::function<void(const TrayOption &option)> callback)
{
    onOptionSelectedCallback = callback;
}

void TrayUI::setVisible(bool visible)
{
    isVisible = visible;
}

void TrayUI::clearOptions()
{
    optionIcons.clear();
    options.clear();
}
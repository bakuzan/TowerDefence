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
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(*window);
        sf::Vector2f mouseWorldPos = window->mapPixelToCoords(mousePixelPos, window->getDefaultView());

        for (size_t i = 0; i < optionIcons.size(); ++i)
        {
            if (optionIcons[i].getGlobalBounds().contains(mouseWorldPos))
            {
                onOptionSelected(optionTypeIds[i]);
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

void TrayUI::addOption(sf::Texture &texture, int optionId, sf::Vector2f iconOffset)
{
    sf::Sprite icon;
    icon.setTexture(texture);
    icon.setPosition(position + iconOffset);
    optionIcons.push_back(icon);
    optionTypeIds.push_back(optionId);
}

void TrayUI::onOptionSelected(int optionId)
{
    // Placeholder function—pass option selection back to GameState
    std::cout << "Selected option ID: " << optionId << std::endl;
}

void TrayUI::setVisible(bool visible)
{
    isVisible = visible;
}

void TrayUI::clearOptions()
{
    optionIcons.clear();
    optionTypeIds.clear();
}
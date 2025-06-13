#include <iostream>

#include "TrayUI.h"

TrayUI::TrayUI(sf::RenderWindow *windowRef, sf::Font &gameFont,
               sf::Vector2f pos, sf::Vector2f size)
    : window(windowRef), font(gameFont), position(pos), isVisible(false)
{
    shadow.setSize(size);
    shadow.setFillColor(sf::Color(0, 0, 0, 100));
    shadow.setPosition(position + sf::Vector2f(2.5f, 2.5f));

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

    if (event.type == sf::Event::MouseMoved)
    {
        sf::Vector2i mousePixelPos(event.mouseMove.x, event.mouseMove.y);
        sf::Vector2f mouseWorldPos = window->mapPixelToCoords(mousePixelPos, window->getDefaultView());

        for (auto &icon : optionIcons)
        {
            if (icon.getGlobalBounds().contains(mouseWorldPos))
            {
                icon.setColor(sf::Color(255, 255, 255, 180)); // Slight transparency on hover
            }
            else
            {
                icon.setColor(sf::Color::White); // Restore default
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

    window.draw(shadow);
    window.draw(background);

    for (const auto &icon : optionIcons)
    {
        window.draw(icon);
    }

    for (const auto &text : optionTexts)
    {
        window.draw(text);
    }
}

void TrayUI::addOption(TrayOption option)
{
    sf::Sprite icon;
    icon.setTexture(option.texture);
    icon.setTextureRect(option.textureRect);

    // Fix the icon to the size that the tray will support
    const sf::Vector2f fixedSize(100.0f, 100.0f);
    sf::Vector2f textureSize(icon.getTextureRect().width, icon.getTextureRect().height);
    icon.setScale(fixedSize.x / textureSize.x, fixedSize.y / textureSize.y);

    float verticalOffset = 5.0f;
    for (const auto &prevIcon : optionIcons)
    {
        verticalOffset += prevIcon.getGlobalBounds().height + 30.0f;
    }

    icon.setPosition(position + sf::Vector2f(10.0f, verticalOffset));

    // Handle text
    sf::Text costText;
    costText.setFont(font);
    costText.setString(std::to_string(option.cost));
    costText.setCharacterSize(20);
    costText.setFillColor(sf::Color::Yellow);
    costText.setPosition(
        icon.getPosition().x + (icon.getGlobalBounds().width / 2) - (costText.getGlobalBounds().width / 2),
        icon.getPosition().y + icon.getGlobalBounds().height + (30.0f / 2) - (costText.getGlobalBounds().height / 2));

    options.push_back(option);
    optionIcons.push_back(icon);
    optionTexts.push_back(costText);
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
    optionTexts.clear();
    optionIcons.clear();
    options.clear();
}
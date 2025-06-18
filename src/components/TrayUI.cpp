#include <iostream>

#include "TrayUI.h"

TrayUI::TrayUI(sf::RenderWindow *windowRef, const sf::Font &gameFont,
               sf::Vector2f pos, sf::Vector2f size)
    : window(windowRef), font(gameFont), position(pos), isVisible(false)
{
    // Tray init
    shadow.setSize(size);
    shadow.setFillColor(sf::Color(0, 0, 0, 100));
    shadow.setPosition(position + sf::Vector2f(2.5f, 2.5f));

    background.setSize(size);
    background.setPosition(pos);
    background.setFillColor(sf::Color(84, 98, 111, 200));

    // Tooltip init
    tooltipBackground.setFillColor(sf::Color(0, 0, 0, 150));
    tooltipBackground.setOutlineThickness(1);
    tooltipBackground.setOutlineColor(sf::Color::White);

    tooltipText.setFont(font);
    tooltipText.setCharacterSize(16);
    tooltipText.setFillColor(sf::Color::White);
    tooltipText.setString("");
}

TrayUI::~TrayUI()
{
    // Destructor
}

// Publics

void TrayUI::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePixelPos(event.mouseButton.x, event.mouseButton.y);
        sf::Vector2f mouseWorldPos = window->mapPixelToCoords(mousePixelPos, window->getDefaultView());

        for (size_t i = 0; i < optionIcons.size(); ++i)
        {
            if (optionIcons[i].getGlobalBounds().contains(mouseWorldPos) &&
                !options[i].isDisabled &&
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
        isTooltipVisible = false;

        for (size_t i = 0; i < optionIcons.size(); ++i)
        {
            sf::Sprite icon = optionIcons[i];
            TrayOption option = options[i];

            if (icon.getGlobalBounds().contains(mouseWorldPos) &&
                !option.isDisabled)
            {
                icon.setColor(sf::Color(255, 255, 255, 180));

                tooltipText.setString(option.name);
                sf::FloatRect textBounds = tooltipText.getLocalBounds();
                tooltipBackground.setSize(sf::Vector2f(textBounds.width + 10, textBounds.height + 10));

                tooltipPosition = mouseWorldPos + sf::Vector2f(15.0f, 10.0f);
                tooltipBackground.setPosition(tooltipPosition - sf::Vector2f(5.0f, 5.0f));
                tooltipText.setPosition(tooltipPosition);

                isTooltipVisible = true;
            }
            else
            {
                icon.setColor(option.isDisabled ? sf::Color::Red : sf::Color::White);
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

    if (isTooltipVisible)
    {
        window.draw(tooltipBackground);
        window.draw(tooltipText);
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
    costText.setFillColor(option.isDisabled ? sf::Color::Red : sf::Color::Yellow);
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
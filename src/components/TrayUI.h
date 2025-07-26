#ifndef TRAYUI_H
#define TRAYUI_H

#include <SFML/Graphics.hpp>

#include <functional>
#include <vector>

#include "data/TrayOption.h"

class TrayUI
{
private:
    sf::RenderWindow *window;
    const sf::Font &font;
    sf::Vector2f position;

    sf::RectangleShape background, shadow;
    std::vector<sf::Sprite> optionIcons;
    std::vector<sf::Text> optionTexts;
    std::vector<TrayOption> options;

    sf::RectangleShape tooltipBackground;
    sf::Text tooltipText;
    sf::Vector2f tooltipPosition;
    bool isTooltipVisible = false;

    bool isVisible;
    std::function<void(const TrayOption &option)> onOptionSelectedCallback;

public:
    TrayUI(sf::RenderWindow *windowRef, const sf::Font &gameFont,
           sf::Vector2f pos, sf::Vector2f size);
    ~TrayUI();

    void handleEvent(sf::Event event);
    void render(sf::RenderWindow &window);

    void addOption(TrayOption option);
    void setOnOptionSelectedCallback(std::function<void(const TrayOption &option)> callback);

    void setVisible(bool visible);
    void clearOptions();
};

#endif // TRAYUI_H

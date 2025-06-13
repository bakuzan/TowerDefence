#ifndef TRAYUI_H
#define TRAYUI_H

#include <SFML/Graphics.hpp>

#include <functional>
#include <vector>

#include "data/TrayOption.h"

class TrayUI
{
private:
    sf::RectangleShape background, shadow;
    std::vector<sf::Sprite> optionIcons;
    std::vector<sf::Text> optionTexts;
    std::vector<TrayOption> options;

    sf::Vector2f position;
    sf::RenderWindow *window;
    sf::Font &font;

    bool isVisible;
    std::function<void(const TrayOption &option)> onOptionSelectedCallback;

public:
    TrayUI(sf::RenderWindow *windowRef, sf::Font &gameFont,
           sf::Vector2f pos, sf::Vector2f size);
    ~TrayUI();

    void handleInput(sf::Event event);
    void render(sf::RenderWindow &window);

    void addOption(TrayOption option);
    void setOnOptionSelectedCallback(std::function<void(const TrayOption &option)> callback);

    void setVisible(bool visible);
    void clearOptions();
};

#endif // TRAYUI_H

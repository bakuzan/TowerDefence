#ifndef TRAYUI_H
#define TRAYUI_H

#include <SFML/Graphics.hpp>

#include <vector>

class TrayUI
{
private:
    sf::RectangleShape background;
    std::vector<sf::Sprite> optionIcons;
    std::vector<int> optionTypeIds;
    sf::Vector2f position;
    sf::RenderWindow *window;

    bool isVisible;

public:
    TrayUI(sf::RenderWindow *windowRef, sf::Vector2f pos, sf::Vector2f size);
    ~TrayUI();

    void handleInput(sf::Event event);
    void render(sf::RenderWindow &window);

    void addOption(sf::Texture &texture, int optionId, sf::Vector2f iconOffset);
    void onOptionSelected(int optionId);

    void setVisible(bool visible);
    void clearOptions();
};

#endif // TRAYUI_H

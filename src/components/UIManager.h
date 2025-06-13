#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>

#include <functional>
#include <vector>

#include "components/TrayUI.h"
#include "data/TrayOption.h"

class UIManager
{
private:
    sf::RenderWindow *window;
    std::vector<sf::Sprite> uiElements;
    TrayUI trayUI;

public:
    UIManager(sf::RenderWindow *gameWindow, sf::Font &gameFont);
    ~UIManager();

    void addUIElement(sf::Sprite element);

    void handleInput(sf::Event event);
    void update();
    void render();

    void showTray(std::vector<TrayOption> options);
    void handleOptionSelection(const TrayOption &option);
};

#endif // UIMANAGER_H

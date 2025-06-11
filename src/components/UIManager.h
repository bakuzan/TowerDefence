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

    std::function<void(int)> onOptionSelectedCallback;

public:
    UIManager(sf::RenderWindow *gameWindow);
    ~UIManager();

    void addUIElement(sf::Sprite element);

    void handleInput(sf::Event event);
    void update();
    void render();

    void setOnOptionSelectedCallback(std::function<void(int)> callback);
    void showTray(std::vector<TrayOption> options);
    void handleOptionSelection(int optionId);
};

#endif // UIMANAGER_H

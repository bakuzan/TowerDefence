#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>

#include <vector>

class UIManager
{
private:
    sf::RenderWindow *window;
    std::vector<sf::Sprite> uiElements;
    TrayUI trayUI;

public:
    UIManager(sf::RenderWindow *gameWindow);
    ~UIManager();

    void addUIElement(sf::Sprite element);

    void handleInput(sf::Event event);
    void update();
    void render();
};

#endif // UIMANAGER_H

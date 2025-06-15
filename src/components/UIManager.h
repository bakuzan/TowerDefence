#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>

#include <functional>
#include <vector>

#include "core/GameData.h"
#include "components/TrayUI.h"
#include "data/TrayOption.h"

class UIManager
{
private:
    const GameData &gameData;
    sf::RenderWindow *window;
    TrayUI trayUI;

    sf::Text scoreText;
    sf::Text goldText;
    sf::Sprite goldIcon;

private:
    void updateUITexts();

public:
    UIManager(sf::RenderWindow *gameWindow, const GameData &data);
    ~UIManager();

    void handleInput(sf::Event event);
    void update();
    void render();

    void showTray(std::vector<TrayOption> options);
    void handleOptionSelection(const TrayOption &option);
};

#endif // UIMANAGER_H

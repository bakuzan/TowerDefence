#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>

#include <functional>
#include <unordered_map>
#include <vector>

#include "core/GameData.h"
#include "components/TrayUI.h"
#include "components/ResultsPanel.h"
#include "data/TrayOption.h"
#include "ui/Button.h"

class UIManager
{
private:
    const GameData &gameData;
    sf::RenderWindow *window;
    TrayUI trayUI;

    sf::Text scoreText;
    sf::Text goldText;
    sf::Sprite goldIcon;
    sf::Text livesText;
    sf::Sprite livesIcon;

    int selectedButtonIndex;
    std::vector<Button> buttons;
    std::unordered_map<std::string, bool> buttonVisibility;

    ResultsPanel resultsPanel;

private:
    void updateUITexts();

public:
    UIManager(sf::RenderWindow *gameWindow, const GameData &data);
    ~UIManager();

    void handleEvent(sf::Event event);
    void update();
    void render();

    void hideTray();
    void showTray(std::vector<TrayOption> options);
    void handleOptionSelection(const TrayOption &option);

    void addButton(const std::string &name,
                   const sf::Vector2f &position,
                   const std::string &text,
                   std::function<void()> callback);
    void setButtonVisible(const std::string &name, bool state);

    void showResultsPanel(const std::string &statsText,
                          std::function<void()> callback);
    void hideResultsPanel();
};

#endif // UIMANAGER_H

#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include <SFML/Graphics.hpp>

#include "ui/Button.h"
#include "core/GameData.h"
#include "core/State.h"
#include "core/StateManager.h"
#include "data/EnvironmentOption.h"

class SettingsState : public State
{
private:
    GameData &gameData;
    StateManager &stateManager;
    sf::RenderWindow &window;
    sf::View settingsView;

    sf::Text gameTitle;

    float buttonSpacing;
    std::vector<Button> buttons;
    int selectedButtonIndex = 0;

    std::vector<EnvironmentOption> envOptions;

    bool shouldReturnToMenuState;

private:
    void updateMenuItemPositions();
    void initEnvironmentOptions();

public:
    SettingsState(GameData &data, StateManager &manager, sf::RenderWindow &win);
    ~SettingsState();

    void handleEvent(const sf::Event &event) override;
    void update(sf::Time deltaTime, sf::RenderWindow &window) override;
    void render(sf::RenderWindow &window) override;
};

#endif // SETTINGSSTATE_H

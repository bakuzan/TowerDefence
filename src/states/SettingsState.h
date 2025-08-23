#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "ui/Button.h"
#include "core/GameData.h"
#include "core/State.h"
#include "core/StateManager.h"
#include "constants/Difficulty.h"
#include "constants/EnvironmentType.h"
#include "data/UIOption.h"

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
    int selectedButtonIndex;

    std::vector<UIOption<Difficulty>> diffOptions;
    std::vector<UIOption<EnvironmentType>> envOptions;

    bool shouldReturnToMenuState;

private:
    void updateMenuItemPositions();
    void initEnvironmentOptions();
    void initDifficultyOptions();

public:
    SettingsState(GameData &data, StateManager &manager, sf::RenderWindow &win);
    ~SettingsState();

    void handleEvent(const sf::Event &event) override;
    void update(sf::Time deltaTime) override;
    void render() override;
};

#endif // SETTINGSSTATE_H

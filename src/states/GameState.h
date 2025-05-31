#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

#include "core/GameData.h"
#include "core/State.h"
#include "core/StateManager.h"

#include "components/PhaseManager.h"
#include "components/UIManager.h"

class GameState : public State
{
private:
    GameData &gameData;
    StateManager &stateManager;
    sf::RenderWindow &window;
    sf::View view;

    PhaseManager phaseManager;
    UIManager uiManager;

    sf::RectangleShape background;

private:
    void ensureBackgroundSizeIsLinkedToViewSize(
        const sf::Vector2f &viewPos,
        const sf::Vector2f &viewSize);

public:
    GameState(GameData &data, StateManager &manager, sf::RenderWindow &window);
    ~GameState();

    void handleEvent(const sf::Event &event) override;
    void update(sf::Time deltaTime, sf::RenderWindow &window) override;
    void render(sf::RenderWindow &window) override;
};

#endif // GAMESTATE_H

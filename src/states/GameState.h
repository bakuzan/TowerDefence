#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

#include "core/GameData.h"
#include "core/State.h"
#include "core/StateManager.h"

#include "components/PhaseManager.h"
#include "components/TileMap.h"
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
    TileMap tileMap;

    float zoomFactor;
    float moveSpeed;

private:
    void loadMap(const std::string filename);
    void adjustZoom(float factor);
    std::vector<TrayOption> getTrayOptions(const TowerSpot &spot);

public:
    GameState(GameData &data, StateManager &manager, sf::RenderWindow &window);
    ~GameState();

    void handleEvent(const sf::Event &event) override;
    void update(sf::Time deltaTime, sf::RenderWindow &window) override;
    void render(sf::RenderWindow &window) override;
};

#endif // GAMESTATE_H

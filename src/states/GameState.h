#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

#include "core/GameData.h"
#include "core/State.h"
#include "core/StateManager.h"

#include "components/EnemySpawnManager.h"
#include "components/ProjectileSpawnManager.h"
#include "components/SoldierSpawnManager.h"
#include "components/PhaseManager.h"
#include "components/TileMap.h"
#include "components/TrayOptionManager.h"
#include "components/UIManager.h"
#include "components/WaveManager.h"
#include "entities/Enemy.h"

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
    TrayOptionManager trayOptionManager;

    EnemySpawnManager enemySpawnManager;
    ProjectileSpawnManager projectileSpawnManager;
    SoldierSpawnManager soldierSpawnManager;
    WaveManager waveManager;

    float zoomFactor;
    float moveSpeed;
    int level;

private:
    void loadMap(const std::string filename);
    void adjustZoom(float factor);

    void handlePlacementOption(sf::Vector2i tileIndex,
                               TowerSpot &spot,
                               int optionId);
    void handleTowerOption(sf::Vector2i tileIndex,
                           TowerSpot &spot,
                           int optionId);
    void onPlayerDeath();
    void onEnemyDeath(Enemy &enemy);

public:
    GameState(GameData &data, StateManager &manager, sf::RenderWindow &window);
    ~GameState();

    void handleEvent(const sf::Event &event) override;
    void update(sf::Time deltaTime, sf::RenderWindow &window) override;
    void render(sf::RenderWindow &window) override;
};

#endif // GAMESTATE_H

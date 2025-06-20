#include <iostream>

#include "utils/GameUtils.h"
#include "utils/InputUtils.h"
#include "constants/Constants.h"
#include "constants/TowerChange.h"
#include "constants/TowerType.h"
#include "data/TrayOption.h"

#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"

GameState::GameState(GameData &data, StateManager &manager, sf::RenderWindow &window)
    : gameData(data),
      stateManager(manager),
      window(window),
      uiManager(&window, data),
      tileMap(gameData.textureManager.getTexture(TextureId::ATLAS),
              15, 15),
      trayOptionManager(data.textureManager, data.rectManager),
      enemySpawnManager(gameData.textureManager.getTexture(TextureId::ENEMIES),
                        data.rectManager),
      zoomFactor(2.5f),
      moveSpeed(60.0f)
{
    loadMap("resources/maps/level_01.txt");

    // Set up ui elements...
    sf::Vector2f buttonSize(Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT);
    sf::Vector2f btnPlacement = GameUtils::getBottomRightPosition(window, buttonSize);
    uiManager.addButton("StartCombat", btnPlacement, "Start", [this]()
                        { phaseManager.advanceToNextPhase(); 
                            uiManager.setButtonVisible("StartCombat", false); });

    // Set up the view
    view.setSize(Constants::VIEW_WIDTH, Constants::VIEW_HEIGHT);
    view.setCenter(tileMap.getCentre());
    view.zoom(zoomFactor);
}

GameState::~GameState()
{
    // Destructor
}

// Publics

void GameState::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::Resized)
    {
        // Maintain the height of the view to match the window height
        float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
        sf::Vector2f previousSize = view.getSize();

        view.setSize((Constants::VIEW_HEIGHT * aspectRatio),
                     Constants::VIEW_HEIGHT);

        float scaleFactor = previousSize.x / view.getSize().x;
        view.zoom(scaleFactor);
    }

    if (event.type == sf::Event::KeyPressed &&
        InputUtils::isAnyKeyPressed(event.key.code, {sf::Keyboard::Escape, sf::Keyboard::P}))
    {
        stateManager.pushState(std::make_unique<PauseState>(gameData, stateManager, window));
    }

    // Camera zoom
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        float scrollDelta = event.mouseWheelScroll.delta;
        float factor = (scrollDelta > 0) ? 0.9f : 1.1f;
        adjustZoom(factor * zoomFactor);
    }

    // Camera panning
    if (event.type == sf::Event::KeyPressed)
    {
        float scaledMoveSpeed = moveSpeed / zoomFactor;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"

        switch (event.key.code)
        {
        case sf::Keyboard::W:
            view.move(0, -scaledMoveSpeed);
            break;
        case sf::Keyboard::S:
            view.move(0, scaledMoveSpeed);
            break;
        case sf::Keyboard::A:
            view.move(-scaledMoveSpeed, 0);
            break;
        case sf::Keyboard::D:
            view.move(scaledMoveSpeed, 0);
            break;
        default:
            break;
        }

#pragma GCC diagnostic pop
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePixelPos(event.mouseButton.x, event.mouseButton.y);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePixelPos, view);
        sf::Vector2i tileIndex = tileMap.isoPointToTileIndex(worldPos);

        auto &towerSpots = gameData.getTowerSpots();
        if (towerSpots.contains(tileIndex))
        {
            TowerSpot &spot = towerSpots.at(tileIndex);

            std::function<void(int)> selectionCallback = [this, tileIndex, &spot](int optionId)
            {
                (spot.hasTower() ? handleTowerOption(tileIndex, spot, optionId)
                                 : handlePlacementOption(tileIndex, spot, optionId));
            };

            std::vector<TrayOption> options = trayOptionManager.getTrayOptions(
                spot,
                gameData.getPlayerGold(),
                selectionCallback);

            uiManager.showTray(options);
        }
    }

    uiManager.handleEvent(event);
}

void GameState::update(sf::Time deltaTime, sf::RenderWindow &window)
{
    float dt = deltaTime.asSeconds();

    // Enemy handling
    if (phaseManager.isAssaultPhase())
    {
        auto &enemies = gameData.getEnemies();

        if (!enemySpawnManager.isWaveActive() &&
            waveManager.hasNextWave())
        {
            const auto &next = waveManager.getCurrentWave();
            enemySpawnManager.setWave(next.spawnGroups);
            waveManager.advanceToNextWave(); // TODO fix this advancement mess
        }

        enemySpawnManager.spawnEnemies(dt, enemies);

        // TODO Update all enemies (movement, state)
    }

    // Tower handling
    std::unordered_map<sf::Vector2i, TowerSpot> &towerSpots = gameData.getTowerSpots();
    for (const auto &[position, spot] : towerSpots)
    {
        if (spot.hasTower())
        {
            spot.tower->update(dt);
        }
    }

    // Projectile handling
    if (phaseManager.isAssaultPhase())
    {
        // TODO Update projectiles, damage, effects
    }

    // UI handling
    uiManager.update();
}

void GameState::render(sf::RenderWindow &window)
{
    // Core gameplay rendering
    window.setView(view);

    std::unordered_map<sf::Vector2i, TowerSpot> &towerSpots = gameData.getTowerSpots();
    tileMap.render(window, towerSpots);

    for (const auto &[position, spot] : towerSpots)
    {
        if (spot.hasTower())
        {
            spot.tower->render(window);
        }
    }

    // UI elements rendering
    uiManager.render();
}

// Private

void GameState::loadMap(const std::string filename)
{
    tileMap.loadMapFromFile(filename);

    auto &towerSpots = gameData.getTowerSpots();
    for (const auto &spot : tileMap.getTowerSpots())
    {
        towerSpots.emplace(spot, TowerSpot{});
    }
}

void GameState::adjustZoom(float newZoomFactor)
{
    float factor = newZoomFactor / zoomFactor;
    zoomFactor = newZoomFactor;
    view.zoom(factor);
    window.setView(view);
}

void GameState::handlePlacementOption(sf::Vector2i tileIndex,
                                      TowerSpot &spot,
                                      int optionId)
{
    TowerType selectedTower = static_cast<TowerType>(optionId);
    gameData.updatePlayerGold(-trayOptionManager.getOptionCost(selectedTower));
    spot.placeTower(
        selectedTower,
        gameData.textureManager.getTexture(TextureId::TOWERS),
        gameData.rectManager.getTextureRects(selectedTower),
        tileMap.tileIndexToIsoPoint(tileIndex.x, tileIndex.y));
}

void GameState::handleTowerOption(sf::Vector2i tileIndex,
                                  TowerSpot &spot,
                                  int optionId)
{
    TowerChange change = static_cast<TowerChange>(optionId);

    switch (change)
    {
    case TowerChange::UPGRADE:
        gameData.updatePlayerGold(-trayOptionManager.getOptionCost(spot));
        spot.tower->levelUp();
        break;
    case TowerChange::REMOVE:
        gameData.updatePlayerGold(trayOptionManager.getRemoveValue(spot));
        spot.removeTower();
        break;
    }
}

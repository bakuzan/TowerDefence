#include <iostream>

#include "utils/GameUtils.h"
#include "utils/InputUtils.h"
#include "constants/Constants.h"
#include "constants/TowerType.h"
#include "data/TrayOption.h"
#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"

GameState::GameState(GameData &data, StateManager &manager, sf::RenderWindow &window)
    : gameData(data),
      stateManager(manager),
      window(window),
      uiManager(&window),
      tileMap(gameData.textureManager.getTexture(TextureId::ATLAS),
              15, 15,
              250, 235,
              140),
      zoomFactor(2.5f),
      moveSpeed(60.0f)
{
    loadMap("resources/maps/level_01.txt");

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
        if (towerSpots.find(tileIndex) != towerSpots.end())
        {
            TowerSpot &spot = towerSpots.at(tileIndex);
            std::vector<TrayOption> trayOptions = getTrayOptions(spot);

            uiManager.showTray(trayOptions);
        }
    }

    uiManager.handleInput(event);
}

void GameState::update(sf::Time deltaTime, sf::RenderWindow &window)
{
    float dt = deltaTime.asSeconds();

    uiManager.update();
}

void GameState::render(sf::RenderWindow &window)
{
    // Core gameplay rendering
    window.setView(view);

    tileMap.render(window);

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

std::vector<TrayOption> GameState::getTrayOptions(const TowerSpot &spot)
{
    std::vector<TrayOption> trayOptions;

    if (spot.hasTower())
    {
        // TODO Upgrades settings...
        // trayOptions.push_back(TrayOption::Create(gameData.textureManager.getTexture("upgrade"),
        //                                          {64, 0, 64, 64},
        //                                          "Upgrade Tower", 2));
        // trayOptions.push_back(TrayOption::Create(gameData.textureManager.getTexture("sell"),
        //                                          {128, 0, 64, 64},
        //                                          "Sell Tower", 3));
    }
    else
    {
        int towerWidth = 64;
        int towerHeight = 64;

        trayOptions.push_back(TrayOption::Create(gameData.textureManager.getTexture(TextureId::TOWERS),
                                                 {0, 0, towerWidth, towerHeight},
                                                 "Melee Tower",
                                                 static_cast<int>(TowerType::MELEE)));
        trayOptions.push_back(TrayOption::Create(gameData.textureManager.getTexture(TextureId::TOWERS),
                                                 {0, 1 * towerHeight, towerWidth, towerHeight},
                                                 "Archer Tower",
                                                 static_cast<int>(TowerType::ARCHER)));
        trayOptions.push_back(TrayOption::Create(gameData.textureManager.getTexture(TextureId::TOWERS),
                                                 {0, 2 * towerHeight, towerWidth, towerHeight},
                                                 "Mage Tower",
                                                 static_cast<int>(TowerType::MAGE)));
    }

    return trayOptions;
}

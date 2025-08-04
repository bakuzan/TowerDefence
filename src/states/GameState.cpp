#include <format>
#include <iostream>

#include "utils/GameUtils.h"
#include "utils/InputUtils.h"
#include "utils/CollisionUtils.h"
#include "constants/Constants.h"
#include "constants/SoldierType.h"
#include "constants/TowerChange.h"
#include "constants/TowerType.h"
#include "data/TrayOption.h"
#include "data/GameOverStateConfig.h"
#include "entities/RangedTower.h"

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
      enemySpawnManager(data.rectManager,
                        gameData.textureManager.getTexture(TextureId::ENEMIES)),
      projectileSpawnManager(data.rectManager),
      soldierSpawnManager(data.rectManager),
      zoomFactor(2.5f),
      moveSpeed(60.0f),
      level(0)
{
    loadMap(gameData.getLevelMap(level));

    // Set up ui elements...
    sf::Vector2f buttonSize(Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT);
    sf::Vector2f btnPlacement = GameUtils::getBottomRightPosition(window, buttonSize);
    uiManager.addButton("StartCombat", btnPlacement, "Start", [this]()
                        { phaseManager.setPhase(Phase::COMBAT); 
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
    auto &enemies = gameData.getEnemies();

    // Enemy handling
    if (phaseManager.isAssaultPhase())
    {
        if (!enemySpawnManager.isWaveActive() &&
            enemies.empty())
        {
            const Wave *wave = waveManager.getNextUnstartedWave();

            if (wave)
            {
                enemySpawnManager.setWave(wave->spawnGroups);
                waveManager.markWaveStarted(wave);
            }
            else
            {
                if (gameData.hasLevelMap(level + 1))
                {
                    // TODO Populate the results text.
                    std::string statsText = std::format("Cleared level {}!", level + 1);
                    uiManager.hideTray();
                    phaseManager.setPhase(Phase::RESULTS);
                    uiManager.showResultsPanel(statsText, [this]()
                                               { level++;
                                            uiManager.hideResultsPanel(); 
                                            loadMap(gameData.getLevelMap(level)); 
                                            phaseManager.setPhase(Phase::PLACEMENT); 
                                            uiManager.setButtonVisible("StartCombat", true); });
                }
                else
                {
                    // In the event there are no more maps:
                    // Trigger GameOverState, but configured to "successful"
                    stateManager.pushState(
                        std::make_unique<GameOverState>(gameData,
                                                        stateManager,
                                                        window,
                                                        GameOverStateConfig::init(
                                                            "Cleared!",
                                                            sf::Color::Green)));
                }
            }
        }

        enemySpawnManager.spawnEnemies(dt,
                                       tileMap.getMapPaths(),
                                       enemies);

        // Update enemies after spawning...
        for (auto it = enemies.begin(); it != enemies.end();)
        {
            (*it)->update(dt);

            if ((*it)->hasReachedGoal())
            {
                it = enemies.erase(it);

                gameData.updatePlayerLives(-1);
                if (gameData.getPlayerLives() <= 0)
                {
                    onPlayerDeath();
                }
            }
            else
            {
                ++it;
            }
        }
    }

    // Tower handling
    auto &soldiers = gameData.getSoldiers();
    auto &projectiles = gameData.getProjectiles();
    std::unordered_map<sf::Vector2i, TowerSpot> &towerSpots = gameData.getTowerSpots();
    for (const auto &[position, spot] : towerSpots)
    {
        if (spot.hasTower())
        {
            spot.tower->update(dt);

            if (auto meleeTower = dynamic_cast<MeleeTower *>(spot.tower.get()))
            {
                if (auto soldierData = meleeTower->getSoldierData(dt))
                {
                    auto newSoldier = soldierSpawnManager.spawnSoldier(
                        gameData.textureManager.getTexture(TextureId::SOLDIER),
                        soldiers,
                        *soldierData,
                        tileMap.tileIndexToIsoPoint(position.x, position.y - 1, true));

                    meleeTower->setDeployedSoldier(newSoldier);
                }
            }

            if (auto rangedTower = dynamic_cast<RangedTower *>(spot.tower.get()))
            {
                if (auto projectile = rangedTower->getShootData(dt, enemies))
                {
                    projectileSpawnManager.spawnProjectile(
                        gameData.textureManager.getTexture(TextureId::PROJECTILES),
                        projectiles,
                        *projectile);
                }
            }
        }
    }

    // Soldier handling
    for (auto soldierIt = soldiers.begin(); soldierIt != soldiers.end();)
    {
        auto &soldier = **soldierIt;
        soldier.update(dt);

        bool removeSoldier = false;
        sf::FloatRect soldierBounds = soldier.getSprite().getGlobalBounds();

        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();)
        {
            auto &enemy = **enemyIt;

            sf::FloatRect enemyBounds = enemy.getSprite().getGlobalBounds();
            sf::FloatRect intersection;

            if (soldierBounds.intersects(enemyBounds, intersection))
            {
                sf::Vector2f direction = enemy.getSprite().getPosition() - soldier.getSprite().getPosition();
                float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

                if (length > 0.f)
                {
                    sf::Vector2f normalized = direction / length;

                    float overlapMagnitude = std::sqrt(intersection.width * intersection.width +
                                                       intersection.height * intersection.height);

                    sf::Vector2f knockback = normalized * (overlapMagnitude / 2.f);

                    enemy.applyDamage(soldier.getDamageInflicts());
                    soldier.applyDamage(enemy.getDamageInflicts());

                    if (enemy.getHealth() <= 0)
                    {
                        onEnemyDeath(enemy);
                        enemyIt = enemies.erase(enemyIt);
                        continue;
                    }
                    else
                    {
                        enemy.getSprite().move(knockback);
                        // soldier.getSprite().move(-knockback);
                        ++enemyIt;
                    }

                    if (soldier.isDead())
                    {
                        removeSoldier = true;
                        break;
                    }
                }
            }
            else
            {
                ++enemyIt;
            }
        }

        if (removeSoldier)
        {
            soldierIt = soldiers.erase(soldierIt);
        }
        else
        {
            ++soldierIt;
        }
    }

    // Projectile handling
    for (auto projIt = projectiles.begin(); projIt != projectiles.end();)
    {
        auto &projectile = **projIt;
        projectile.update(dt, enemies);

        bool isRemoved = false;

        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();)
        {
            auto &enemy = **enemyIt;

            if (projectile.getSprite().getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds()) &&
                CollisionUtils::checkSpritesIntersect(projectile.getSprite(), enemy.getSprite()))
            {
                enemy.applyDamage(projectile.getDamageInflicts());

                if (enemy.getHealth() <= 0)
                {
                    onEnemyDeath(enemy);

                    enemyIt = enemies.erase(enemyIt);
                }

                projIt = projectiles.erase(projIt);
                isRemoved = true;
                break;
            }
            else
            {
                ++enemyIt;
            }
        }

        if (!isRemoved)
        {
            if (projectile.canBeRemoved())
            {
                projIt = projectiles.erase(projIt);
            }
            else
            {
                ++projIt;
            }
        }
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

    auto &enemies = gameData.getEnemies();
    for (const auto &enemy : enemies)
    {
        enemy->render(window);
    }

    for (const auto &[position, spot] : towerSpots)
    {
        if (spot.hasTower())
        {
            spot.tower->render(window);
        }
    }

    auto &soldiers = gameData.getSoldiers();
    for (const auto &soldier : soldiers)
    {
        soldier->render(window);
    }

    auto &projectiles = gameData.getProjectiles();
    for (const auto &projectile : projectiles)
    {
        projectile->render(window);
    }

    // UI elements rendering
    uiManager.render();
}

// Private

void GameState::loadMap(const std::string filename)
{
    tileMap.loadMapFromFile(filename);

    gameData.resetLevel();

    auto &towerSpots = gameData.getTowerSpots();
    for (const auto &spot : tileMap.getTowerSpots())
    {
        towerSpots.emplace(spot, TowerSpot{});
    }

    waveManager.reset();
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
    (void)tileIndex;

    TowerChange change = static_cast<TowerChange>(optionId);

    switch (change)
    {
    case TowerChange::UPGRADE:
        gameData.updatePlayerGold(-trayOptionManager.getOptionCost(spot));
        spot.tower->levelUp();
        break;
    case TowerChange::REMOVE:
    {
        gameData.updatePlayerGold(trayOptionManager.getRemoveValue(spot));

        if (spot.tower->getType() == TowerType::MELEE)
        {
            auto &soldiers = gameData.getSoldiers();
            auto *meleeTower = dynamic_cast<MeleeTower *>(spot.tower.get());

            soldiers.erase(
                std::remove_if(soldiers.begin(), soldiers.end(),
                               [&meleeTower](const std::shared_ptr<Soldier> &s)
                               {
                                   auto towerSoldier = meleeTower->getSoldier().lock();
                                   return towerSoldier &&
                                          towerSoldier == s;
                               }),
                soldiers.end());
        }

        spot.removeTower();
        break;
    }
    }
}

void GameState::onPlayerDeath()
{
    stateManager.pushState(std::make_unique<GameOverState>(gameData, stateManager, window));
}

void GameState::onEnemyDeath(Enemy &enemy)
{
    gameData.updatePlayerScore(enemy.getPointsValue());
    gameData.updatePlayerGold(enemy.getPointsValue());
}
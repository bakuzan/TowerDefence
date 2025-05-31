#include "utils/GameUtils.h"
#include "utils/InputUtils.h"
#include "constants/Constants.h"
#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"

GameState::GameState(GameData &data, StateManager &manager, sf::RenderWindow &window)
    : gameData(data),
      stateManager(manager),
      window(window),
      uiManager(&window)
{
    // Load background TODO restore when have background
    // const sf::Texture &backgroundTexture = gameData.textureManager.getTexture(TextureId::BACKGROUND);
    // background.setTexture(&backgroundTexture);

    // Set up the view
    view.setSize(Constants::VIEW_WIDTH, Constants::VIEW_HEIGHT);
    ensureBackgroundSizeIsLinkedToViewSize(
        view.getCenter() - view.getSize() / 2.0f,
        view.getSize());
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
        view.setSize(Constants::VIEW_HEIGHT * aspectRatio, Constants::VIEW_HEIGHT);
        ensureBackgroundSizeIsLinkedToViewSize(
            view.getCenter() - view.getSize() / 2.0f,
            view.getSize());
    }

    if (event.type == sf::Event::KeyPressed &&
        InputUtils::isAnyKeyPressed(event.key.code, {sf::Keyboard::Escape, sf::Keyboard::P}))
    {
        stateManager.pushState(std::make_unique<PauseState>(gameData, stateManager, window));
    }

    uiManager.handleInput(event);
}

void GameState::update(sf::Time deltaTime, sf::RenderWindow &window)
{
    float dt = deltaTime.asSeconds();

    uiManager.update();

    // Update background texture rect for tiling by matching the view
    sf::Vector2f viewPos = view.getCenter() - view.getSize() / 2.0f;
    ensureBackgroundSizeIsLinkedToViewSize(
        viewPos,
        view.getSize());
}

void GameState::render(sf::RenderWindow &window)
{
    // Core gameplay rendering
    window.setView(view);

    // UI elements rendering
    uiManager.render();
}

// Private

void GameState::ensureBackgroundSizeIsLinkedToViewSize(
    const sf::Vector2f &viewPos,
    const sf::Vector2f &viewSize)
{
    background.setSize(viewSize);
    background.setPosition(viewPos);
    background.setTextureRect(sf::IntRect(
        static_cast<int>(viewPos.x),
        static_cast<int>(viewPos.y),
        static_cast<int>(viewSize.x),
        static_cast<int>(viewSize.y)));
}

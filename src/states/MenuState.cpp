#include "constants/Constants.h"
#include "GameState.h"
#include "utils/InputUtils.h"
#include "MenuState.h"
#include "SettingsState.h"

MenuState::MenuState(GameData &data, StateManager &manager, sf::RenderWindow &win)
    : gameData(data), stateManager(manager), window(win)
{
    buttonSpacing = Constants::BUTTON_HEIGHT + 10.f;
    sf::Vector2f center(menuView.getCenter());
    window.setView(menuView);

    // Setup title
    gameTitle.setFont(gameData.gameFont);
    gameTitle.setString("Tower Defence");
    gameTitle.setCharacterSize(48);
    gameTitle.setFillColor(sf::Color::White);

    // Add buttons
    buttons.emplace_back("New", gameData.gameFont, "New Game",
                         sf::Vector2f(center.x - 100.f, center.y - 60.f),
                         [this]()
                         { stateManager.changeState(std::make_unique<GameState>(gameData, stateManager, window)); });
    buttons.emplace_back("Settings", gameData.gameFont, "Settings",
                         sf::Vector2f(center.x - 100.f, center.y + buttonSpacing),
                         [this]()
                         { stateManager.changeState(std::make_unique<SettingsState>(gameData, stateManager, window)); });
    buttons.emplace_back("Exit", gameData.gameFont, "Exit",
                         sf::Vector2f(center.x - 100.f, center.y + (buttonSpacing * 2.0f)),
                         [this]()
                         { window.close(); });

    // To ensure positioning is updated relative to window resizing
    updateMenuItemPositions();
}

MenuState::~MenuState()
{
    // Destructor
}

// Publics

void MenuState::handleEvent(const sf::Event &event)
{
    InputUtils::handleButtonEvent(event, buttons, window, selectedButtonIndex);

    if (event.type == sf::Event::Resized)
    {
        updateMenuItemPositions();
    }
}

void MenuState::update(sf::Time deltaTime, sf::RenderWindow &window)
{
    (void)deltaTime;
    (void)window;

    gameData.audioManager.cleanupSounds();
}

void MenuState::render(sf::RenderWindow &window)
{
    window.setView(menuView);
    window.draw(gameTitle);

    for (const auto &button : buttons)
    {
        button.render(window);
    }
}

// Privates
void MenuState::updateMenuItemPositions()
{
    sf::Vector2f viewCenter = menuView.getCenter();
    sf::Vector2f viewSize = menuView.getSize();

    gameTitle.setPosition(viewCenter.x - viewSize.x / 2.f + 25.f,
                          viewCenter.y - viewSize.y / 2.f + 25.f);

    float offsetX = Constants::BUTTON_WIDTH / 2.0f;
    buttons[0].setPosition(sf::Vector2f(viewCenter.x - offsetX, viewCenter.y - (buttonSpacing / 2.0f)));
    buttons[1].setPosition(sf::Vector2f(viewCenter.x - offsetX, viewCenter.y + (buttonSpacing / 2.0f)));
    buttons[2].setPosition(sf::Vector2f(viewCenter.x - offsetX, viewCenter.y + (buttonSpacing * 1.5f)));
}

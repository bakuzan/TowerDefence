#include "utils/GameUtils.h"

#include "UIManager.h"

UIManager::UIManager(sf::RenderWindow *gameWindow, const GameData &data)
    : window(gameWindow),
      gameData(data),
      trayUI(gameWindow,
             data.gameFont,
             sf::Vector2f(0.0f, (gameWindow->getSize().y - 400.0f) / 2.0f),
             sf::Vector2f(120.0f, 400.0f))
{
    updateUITexts(); // Initial text so size checks work out correct below.

    // Score UI setup
    scoreText.setFont(gameData.gameFont);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(
        gameWindow->getSize().x - scoreText.getGlobalBounds().width - 10,
        20);

    // Gold UI setup
    goldText.setFont(gameData.gameFont);
    goldText.setCharacterSize(24);
    goldText.setFillColor(sf::Color::Yellow);
    goldText.setPosition(40, 20);

    // TODO get a coin texture...
    // goldIcon.setTexture(yourGoldTexture);
    // goldIcon.setPosition(10, 20);
}

UIManager::~UIManager()
{
    // Destructor
}

// Publics

void UIManager::handleInput(sf::Event event)
{
    sf::View prevView = window->getView();
    window->setView(window->getDefaultView()); // Switch to UI view

    trayUI.handleInput(event);

    window->setView(prevView); // Restore previous view
}

void UIManager::update()
{
    updateUITexts();
}

void UIManager::render()
{
    sf::View prevView = window->getView();
    window->setView(window->getDefaultView()); // Switch to UI view

    window->draw(scoreText);
    window->draw(goldText);

    trayUI.render(*window);

    window->setView(prevView); // Restore previous view
}

void UIManager::showTray(std::vector<TrayOption> options)
{
    trayUI.clearOptions();

    for (const TrayOption option : options)
    {
        trayUI.addOption(option);
    }

    std::function<void(const TrayOption &)> selectionCallback =
        [this](const TrayOption &option)
    { handleOptionSelection(option); };

    trayUI.setOnOptionSelectedCallback(selectionCallback);
    trayUI.setVisible(true);
}

void UIManager::handleOptionSelection(const TrayOption &option)
{
    trayUI.setVisible(false);
    option.onSelected(option.optionId);
}

// Privates

void UIManager::updateUITexts()
{
    scoreText.setString(GameUtils::formatScoreText(gameData.getPlayerScore()));
    goldText.setString(std::to_string(gameData.getPlayerGold()));
}
#include "utils/GameUtils.h"
#include "utils/InputUtils.h"

#include "UIManager.h"

UIManager::UIManager(sf::RenderWindow *gameWindow, const GameData &data)
    : window(gameWindow),
      gameData(data),
      trayUI(gameWindow,
             data.gameFont,
             sf::Vector2f(0.0f, (gameWindow->getDefaultView().getSize().y - 400.0f) / 2.0f),
             sf::Vector2f(120.0f, 400.0f)),
      selectedButtonIndex(-1)
{
    updateUITexts(); // Initial text so size checks work out correct below.

    // Score UI setup
    scoreText.setFont(gameData.gameFont);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(
        gameWindow->getDefaultView().getSize().x - scoreText.getGlobalBounds().width - 10,
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

void UIManager::handleEvent(sf::Event event)
{
    sf::View prevView = window->getView();
    window->setView(window->getDefaultView()); // Switch to UI view

    InputUtils::handleButtonEvent(event, buttons, *window, selectedButtonIndex);

    if (event.type == sf::Event::Resized)
    {
        for (Button &button : buttons)
        {
            if (button.getName() == "StartCombat" &&
                buttonVisibility[button.getName()])
            {
                button.setPosition(GameUtils::getBottomRightPosition(*window));
            }
        }
    }

    trayUI.handleEvent(event);

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

    for (Button &button : buttons)
    {
        if (buttonVisibility[button.getName()])
        {
            button.render(*window);
        }
    }

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

void UIManager::addButton(const std::string &name,
                          const sf::Vector2f &position,
                          const std::string &text,
                          std::function<void()> callback)
{
    buttons.emplace_back(name, gameData.gameFont, text, position, callback);
    buttonVisibility[name] = true;
}

void UIManager::setButtonVisible(const std::string &name, bool state)
{
    if (buttonVisibility.find(name) != buttonVisibility.end())
    {
        buttonVisibility[name] = state;
    }
}

// Privates

void UIManager::updateUITexts()
{
    scoreText.setString(GameUtils::formatScoreText(gameData.getPlayerScore()));
    goldText.setString(std::to_string(gameData.getPlayerGold()));
}

std::vector<Button> UIManager::getButtonVector()
{
    std::vector<Button> buttonVector;
    buttonVector.reserve(buttons.size());

    for (const Button &button : buttons)
    {
        if (buttonVisibility[button.getName()])
        {
            buttonVector.push_back(button);
        }
    }

    return buttonVector;
}

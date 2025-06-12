#include "UIManager.h"

UIManager::UIManager(sf::RenderWindow *gameWindow)
    : window(gameWindow),
      trayUI(gameWindow,
             sf::Vector2f(0.0f, 0.0f), sf::Vector2f(60.0f, 160.0f))
{
    // Constructor
}

UIManager::~UIManager()
{
    // Destructor
}

// Publics

void UIManager::addUIElement(sf::Sprite element)
{
    uiElements.push_back(element);
}

void UIManager::handleInput(sf::Event event)
{
    sf::View prevView = window->getView();
    window->setView(window->getDefaultView()); // Switch to UI view

    trayUI.handleInput(event);

    window->setView(prevView); // Restore previous view
}

void UIManager::update()
{
    // Handle UI interactions, animations, etc.
}

void UIManager::render()
{
    sf::View prevView = window->getView();
    window->setView(window->getDefaultView()); // Switch to UI view

    for (auto &element : uiElements)
    {
        window->draw(element);
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
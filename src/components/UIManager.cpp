#include "UIManager.h"

UIManager::UIManager(sf::RenderWindow *gameWindow)
    : window(gameWindow),
      trayUI(gameWindow, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(60.0f, 160.0f))
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

void UIManager::setOnOptionSelectedCallback(std::function<void(int)> callback)
{
    onOptionSelectedCallback = callback;
}

void UIManager::showTray(std::vector<int> options)
{
    trayUI.clearOptions();
    sf::Texture texture;

    for (int optionId : options)
    {
        trayUI.addOption(texture, optionId, sf::Vector2f());
    }

    trayUI.setVisible(true);
}

void UIManager::handleOptionSelection(int optionId)
{
    trayUI.setVisible(false);

    if (onOptionSelectedCallback)
    {
        onOptionSelectedCallback(optionId);
    }
}
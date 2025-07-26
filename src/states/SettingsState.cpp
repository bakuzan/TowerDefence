#include <iostream>

#include "SettingsState.h"
#include "MenuState.h"

#include "components/SettingsManager.h"
#include "constants/Constants.h"
#include "utils/InputUtils.h"

SettingsState::SettingsState(GameData &data, StateManager &manager, sf::RenderWindow &win)
    : gameData(data), stateManager(manager), window(win),
      shouldReturnToMenuState(false)
{
    std::cerr << "[SettingsState] Constructing state\n";
    std::cerr << "[SettingsState] settingsView size: "
              << settingsView.getSize().x << ", " << settingsView.getSize().y
              << "\n";

    buttonSpacing = Constants::BUTTON_HEIGHT + 10.f;
    // window.setView(settingsView);
    sf::Vector2f viewSize = settingsView.getSize();

    // Setup title
    gameTitle.setFont(gameData.gameFont);
    gameTitle.setString("Settings");
    gameTitle.setCharacterSize(48);
    gameTitle.setFillColor(sf::Color::White);

    // Add buttons
    buttons.emplace_back("Save", data.gameFont, "Save", sf::Vector2f(viewSize.x - Constants::BUTTON_WIDTH, viewSize.y - buttonSpacing),
                         [this]()
                         { SettingsManager::getInstance().save();
                            shouldReturnToMenuState=true; });
    buttons.emplace_back("Back", data.gameFont, "Back", sf::Vector2f(10.0f, viewSize.y - buttonSpacing),
                         [this]()
                         { SettingsManager::getInstance().reset();
                            shouldReturnToMenuState=true; });

    initEnvironmentOptions();

    // To ensure positioning is updated relative to window resizing
    updateMenuItemPositions();
}

SettingsState::~SettingsState()
{
    // Destructor
}

// Publics

void SettingsState::handleEvent(const sf::Event &event)
{
    std::cerr << "[HandleEvent]...\n";
    InputUtils::handleButtonEvent(event, buttons, window, selectedButtonIndex);

    if (event.type == sf::Event::Resized)
    {
        updateMenuItemPositions();
    }

    if (event.type == sf::Event::EventType::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Button::Left)
    {
        sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
        sf::Vector2f mouseWorldPos = window.mapPixelToCoords(pixelPos);

        for (auto &opt : envOptions)
        {
            if (opt.box.getGlobalBounds().contains(mouseWorldPos))
            {
                SettingsManager::getInstance().setEnvironmentType(opt.type);
            }
        }
    }
}

void SettingsState::update(sf::Time deltaTime, sf::RenderWindow &window)
{
    std::cerr << "[Update]...\n";
    if (shouldReturnToMenuState)
    {
        stateManager.changeState(std::make_unique<MenuState>(gameData, stateManager, window));
    }
}

void SettingsState::render(sf::RenderWindow &window)
{
    std::cerr << "[Render] Drawing buttons...\n";
    window.setView(settingsView);
    window.draw(gameTitle);

    EnvironmentType selected = SettingsManager::getInstance().getEnvironmentType();

    for (auto &opt : envOptions)
    {
        if (opt.type == selected)
        {
            opt.box.setFillColor(sf::Color::Green);
        }
        else
        {
            opt.box.setFillColor(sf::Color::White);
        }

        window.draw(opt.box);
        window.draw(opt.label);
    }

    for (const auto &button : buttons)
    {
        button.render(window);
    }
}

// Privates

void SettingsState::updateMenuItemPositions()
{
    std::cerr << "[SettingsState] updateMenuItemPositions\n";
    sf::Vector2f viewCenter = settingsView.getCenter();
    sf::Vector2f viewSize = settingsView.getSize();

    // gameTitle.setPosition(viewCenter.x - viewSize.x / 2.f + 25.f,
    //                       viewCenter.y - viewSize.y / 2.f + 25.f);
    std::cerr << "[SettingsState] updateMenuItemPositions...buttons\n";
    buttons[0].setPosition(sf::Vector2f(viewSize.x - Constants::BUTTON_WIDTH - 10.0f, viewSize.y - buttonSpacing));
    buttons[1].setPosition(sf::Vector2f(10.0f, viewSize.y - buttonSpacing));
    std::cerr << "[SettingsState] updateMenuItemPositions...buttons DONE\n";
}

void SettingsState::initEnvironmentOptions()
{
    std::cerr << "[SettingsState] initEnvironmentOptions\n";
    const std::vector<std::string> names = {"Spring", "Winter", "Desert"};
    const std::vector<EnvironmentType> types = {
        EnvironmentType::SPRING, EnvironmentType::WINTER, EnvironmentType::DESERT};

    const float spacing = 20.f;
    const float boxWidth = 150.f;
    const float boxHeight = 40.f;
    const sf::Vector2f startPos(25.f, 200.f);

    for (size_t i = 0; i < types.size(); ++i)
    {
        EnvironmentOption opt;
        opt.type = types[i];

        opt.box.setSize({boxWidth, boxHeight});
        opt.box.setPosition({startPos.x + i * (boxWidth + spacing), startPos.y});
        opt.box.setFillColor(sf::Color::White);

        opt.label.setFont(gameData.gameFont);
        opt.label.setString(names[i]);
        opt.label.setCharacterSize(18);
        opt.label.setFillColor(sf::Color::Black);
        opt.label.setPosition(opt.box.getPosition() + sf::Vector2f(10.f, 5.f));

        envOptions.push_back(opt);
    }
}
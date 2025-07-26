#include "ResultsPanel.h"

#include "constants/Constants.h"
#include "utils/GameUtils.h"

ResultsPanel::ResultsPanel()
    : isVisible(false)
{
}

ResultsPanel::~ResultsPanel()
{
    // Destructor
}

// Publics

void ResultsPanel::init(const sf::Font &font,
                        const sf::RenderWindow &window,
                        std::function<void()> nextLevelCallback)
{
    sf::View view = window.getDefaultView();
    sf::Vector2f viewSize = view.getSize();
    sf::Vector2f viewCenter = view.getCenter();

    // Background overlay
    sf::Vector2f backgroundSize(viewSize.x - 20.0f, viewSize.y - 20.0f);
    background.setSize(backgroundSize);
    background.setFillColor(sf::Color(0, 0, 0, 150));
    background.setPosition(viewCenter.x - backgroundSize.x / 2.f,
                           viewCenter.y - backgroundSize.y / 2.f);

    // Victory Title
    victoryTitle.setFont(font);
    victoryTitle.setCharacterSize(48);
    victoryTitle.setFillColor(sf::Color::Green);
    victoryTitle.setString("Cleared!");

    float topEdge = viewCenter.y - viewSize.y / 2.0f;
    victoryTitle.setPosition(
        viewCenter.x - (victoryTitle.getGlobalBounds().width / 2.0f),
        topEdge + 10.0f);

    // Stats Text
    statsText.setFont(font);
    statsText.setCharacterSize(20);
    statsText.setFillColor(sf::Color::White);

    float leftEdge = viewCenter.x - viewSize.x / 2.0f;
    statsText.setPosition(
        leftEdge + 10.0f,
        topEdge + victoryTitle.getGlobalBounds().height + 25.0f);

    // Next Level Button
    sf::Vector2f buttonSize(Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT);
    sf::Vector2f btnPlacement = GameUtils::getBottomRightPosition(window, buttonSize);

    nextLevelButton = std::make_unique<Button>("nextLevel", font, "Next Level",
                                               btnPlacement, nextLevelCallback);
}

void ResultsPanel::setStatsText(const std::string &stats)
{
    statsText.setString(stats);
}

void ResultsPanel::toggleVisible()
{
    isVisible = !isVisible;
}

void ResultsPanel::handleEvent(const sf::Event &event,
                               const sf::RenderWindow &window)
{
    if (!isVisible)
    {
        return;
    }

    sf::Vector2i mousePos;

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        mousePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);

        if (nextLevelButton->isMouseOver(mousePos, window))
        {
            nextLevelButton->trigger();
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        mousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
        nextLevelButton->onHover(nextLevelButton->isMouseOver(mousePos, window));
    }
}

void ResultsPanel::render(sf::RenderWindow &window)
{
    if (isVisible)
    {
        window.draw(background);
        window.draw(victoryTitle);
        window.draw(statsText);
        nextLevelButton->render(window);
    }
}

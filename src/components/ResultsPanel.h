#ifndef RESULTSPANEL_H
#define RESULTSPANEL_H

#include <SFML/Graphics.hpp>

#include <functional>
#include <memory>

#include "ui/Button.h"

class ResultsPanel
{
private:
    sf::RectangleShape background;
    sf::Text victoryTitle;
    sf::Text statsText;
    std::unique_ptr<Button> nextLevelButton;
    sf::FloatRect nextLevelButtonBounds;
    bool isVisible;

public:
    ResultsPanel();
    ~ResultsPanel();

    void init(const sf::Font &font,
              const sf::RenderWindow &window,
              std::function<void()> nextLevelCallback);
    void setStatsText(const std::string &stats);
    void toggleVisible();

    void handleEvent(const sf::Event &event, const sf::RenderWindow &window);
    void render(sf::RenderWindow &window);
};

#endif // RESULTSPANEL_H
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

#include <functional>

class Button
{
private:
    sf::RectangleShape shape;
    sf::Text text;
    std::function<void()> action;

public:
    Button(const sf::Font &font,
           const std::string &label,
           sf::Vector2f position,
           std::function<void()> action);
    ~Button();

    void render(sf::RenderWindow &window) const;
    void onHover(bool isHovered);
    bool isMouseOver(sf::Vector2i mousePosition, const sf::RenderWindow &window) const;
    void trigger() const;
    void setPosition(sf::Vector2f position);
};

#endif // BUTTON_H

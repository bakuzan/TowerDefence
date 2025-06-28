#ifndef ORDERINGUTILITIES_H
#define ORDERINGUTILITIES_H

#include <SFML/System.hpp>
#include <tuple>

template <typename T>
struct Vector2Comparator
{
    bool operator()(const sf::Vector2<T> &a, const sf::Vector2<T> &b) const
    {
        return std::tie(a.x, a.y) < std::tie(b.x, b.y);
    }
};

#endif // ORDERINGUTILITIES_H

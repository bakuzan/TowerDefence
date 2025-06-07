#ifndef HASHUTILITIES_H
#define HASHUTILITIES_H

#include <SFML/System.hpp>
#include <functional>

namespace std
{
    template <>
    struct hash<sf::Vector2<int>>
    {
        size_t operator()(const sf::Vector2<int> &v) const noexcept
        {
            return hash<int>()(v.x) ^ (hash<int>()(v.y) << 1);
        }
    };
}

#endif // HASHUTILITIES_H

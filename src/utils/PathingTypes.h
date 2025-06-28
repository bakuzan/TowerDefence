#ifndef PATHINGTYPES_H
#define PATHINGTYPES_H

#include <SFML/System.hpp>

#include <vector>
#include <map>
#include "OrderingUtilities.h"

using Path = std::vector<sf::Vector2f>;
using PathMap = std::map<sf::Vector2i, Path, Vector2Comparator<int>>;

#endif // PATHINGTYPES_H

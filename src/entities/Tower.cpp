#include "Tower.h"

Tower::Tower()
    : level(1)
{
    // Constructor
}

Tower::~Tower()
{
    // Destructor
}

// Publics

const int Tower::getLevel() const
{
    return level;
}
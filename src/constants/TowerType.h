#pragma once

#include <cstddef>

enum class TowerType
{
    MELEE = 0,
    ARCHER,
    MAGE,
};

struct TowerTypeHash
{
    std::size_t operator()(TowerType type) const noexcept
    {
        return static_cast<std::size_t>(type);
    }
};
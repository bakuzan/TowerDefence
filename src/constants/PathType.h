#pragma once

enum class PathType
{
    STRAIGHT_VERTICAL = 0,
    STRAIGHT_HORIZONTAL,
    CROSSROAD,
    T_UPWARDS,
    T_RIGHT,
    T_DOWNWARDS,
    T_LEFT,
    CORNER_TOP_RIGHT,
    CORNER_BOTTOM_LEFT,
    CORNER_TOP_LEFT,
    CORNER_BOTTOM_RIGHT,
};
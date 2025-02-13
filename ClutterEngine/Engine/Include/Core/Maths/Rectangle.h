#pragma once
#include "Vectors/Vector2.h"

/**
 * @brief Enumeration for the sides of a rectangle.
 */
enum Face
{
    NONE,  ///< No collision.
    LEFT,  ///< Collision on the left side.
    RIGHT, ///< Collision on the right side.
    UP,    ///< Collision on the upper side.
    DOWN   ///< Collision on the lower side.
};

/**
 * @brief A structure representing a rectangle.
 */
struct Rectangle
{
    Vector2 location;   ///< The location of the rectangle.
    Vector2 dimensions; ///< The dimensions of the rectangle.

};
#pragma once
#include <Core/Maths/Vectors/Vector2.h>
#include <Core/Maths/Transforms/Transform.h>
#include <Core/Maths/Maths.h>

/**
 * @brief Represents a 2D transformation including location, scale, and rotation.
 */
struct CLUTTER_API Transform2D
{
    /**
     * @brief The position of the transform in 2D space.
     */
    Vector2 location = { 0, 0 };

    /**
     * @brief The scale of the transform in 2D space.
     */
    Vector2 scale = { 1, 1 };

    /**
     * @brief The rotation of the transform in radians.
     */
    float rotation = 0;

    /**
     * @brief Default constructor. Initializes to identity transform.
     */
    Transform2D() : location({ 0,0 }), scale({ 1,1 }), rotation(0) {};

    /**
     * @brief Constructs a Transform2D with specified location, scale, and rotation.
     * @param pLocation The position in 2D space.
     * @param pScale The scale in 2D space.
     * @param pRotation The rotation in radians.
     */
    Transform2D(Vector2 pLocation, Vector2 pScale, float pRotation) : location(pLocation), scale(pScale), rotation(pRotation) {};

    /**
     * @brief Gets the right direction vector based on the current rotation.
     * @return The right direction as a Vector2.
     */
    Vector2 Right() const { return Vector2(Maths::Cos(rotation), -Maths::Sin(rotation)); }

    /**
     * @brief Gets the up direction vector based on the current rotation.
     * @return The up direction as a Vector2.
     */
    Vector2 Up() const { return Vector2(Maths::Sin(rotation), -Maths::Cos(rotation)); }

    /**
     * @brief Converts this 2D transform to a 3D transform.
     * @return The corresponding 3D Transform.
     */
    inline Transform To3D()
    {
        Transform temp;

        temp.SetScale(scale);
        temp.SetRotation(rotation);
        temp.SetLocation(location);

        return temp;
    }

    /**
     * @brief Adds two Transform2D objects component-wise.
     * @param left The first Transform2D.
     * @param right The second Transform2D.
     * @return The result of the addition.
     */
    friend Transform2D operator+(Transform2D left, Transform2D right)
    {
        return { left.location + right.location, left.scale * right.scale, left.rotation + right.rotation };
    }
};

#pragma once
#include <Core/Maths/Vectors/Vector2.h>
#include <Core/Maths/Maths.h>

struct Transform2D
{
    Vector2 location = { 0, 0 };
    Vector2 scale = { 1, 1 };

    float rotation = 0;

    Transform2D() : location({ 0,0 }), scale({ 1,1 }), rotation(0) {};
    Transform2D(Vector2 pLocation, Vector2 pScale, float pRotation) : location(pLocation), scale(pScale), rotation(pRotation) {};

    Vector2 Right() const { return Vector2(Maths::Cos(rotation), -Maths::Sin(rotation)); }
    Vector2 Up() const { return Vector2(Maths::Sin(rotation), -Maths::Cos(rotation)); }

    friend Transform2D operator+(Transform2D left, Transform2D right)
    {
        return { left.location + right.location, left.scale * right.scale, left.rotation + right.rotation };
    }
};
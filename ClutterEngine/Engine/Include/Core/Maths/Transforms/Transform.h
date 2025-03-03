#pragma once
#include <Core/Maths/Vectors/Vector3.h>
#include <Core/Maths/Quaternion.h>
#include <Core/Maths/Maths.h>

struct Transform
{
    Vector3 location = { 0, 0, 0 };
    Vector3 scale = { 1, 1, 1 };

    Quaternion rotation {0, 0, 0, 0};

    Vector3 Right() const 
    {
        float yaw = Maths::ToRad(rotation.y);
        Vector3 tempRight = { Maths::Cos(yaw), 0, Maths::Sin(yaw) };

        return Vector3::Normalize(tempRight);
    }

    Vector3 Up() const 
    {
        float pitch = Maths::ToRad(rotation.x);
        float roll = Maths::ToRad(rotation.z);
        Vector3 tempUp = { -Maths::Sin(pitch) * Maths::Sin(roll), Maths::Cos(pitch), Maths::Sin(pitch) * Maths::Cos(roll) };

        return Vector3::Normalize(tempUp);
    }

    Vector3 Forward() const 
    {
        float yaw = Maths::ToRad(rotation.y);
        float pitch = Maths::ToRad(rotation.x);
        Vector3 tempForward = { -Maths::Sin(yaw) * Maths::Cos(pitch),  Maths::Sin(pitch),  -Maths::Cos(yaw) * Maths::Cos(pitch) };
        return Vector3::Normalize(tempForward);
    }
};
#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Quaternion.h>
#include <Core/Maths/Matrix/Matrix4Row.h>
#include <Core/Maths/Maths.h>

class CLUTTER_API Transform
{
    Vector3 location = { 0, 0, 0 };
    Vector3 scale = { 1, 1, 1 };

    Quaternion rotation {0, 0, 0, 1};
    Matrix4Row mWorldTransform;

    bool mDirty = true;

public:

    Transform() { mDirty = true; };
    Transform(Vector3 pLocation, Vector3 pScale, Quaternion pRotation) : location(pLocation), scale(pScale), rotation(pRotation) { mDirty = true; };

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

    void SetLocation(Vector3 newLocation)
    {
        location = newLocation;
        mDirty = true;
    }

    void SetLocation(Vector2 newLocation)
    {
        location = newLocation;
        mDirty = true;
    }

    void SetRotation(Quaternion newRotation)
    {
        newRotation.Normalize();
        rotation = newRotation;
        mDirty = true;
    }

    void SetRotation(float newRotation)
    {
        rotation = newRotation;
        rotation.Normalize();
        mDirty = true;
    }

    void SetScale(Vector3 newScale)
    {
        scale = newScale;
        mDirty = true;
    }

    void SetScale(Vector2 newScale)
    {
        scale = newScale;
        mDirty = true;
    }

    Transform operator+(const Transform& q) const
    {
        return { location + q.location, scale * q.scale, Quaternion::Concatenate(q.rotation, rotation) };
    }

    Vector3 Location() const { return location; };
    Vector3 Scale() const { return scale; };
    Quaternion Rotation() const { return rotation; };
    Matrix4Row GetMat4Transform() const 
    { 
        if (mDirty)
        {
            const_cast<Transform*>(this)->ComputeWorldTransform();
        }
        return mWorldTransform; 
    };

    void ComputeWorldTransform()
    {
        mWorldTransform = Matrix4Row::CreateScale(scale);
        mWorldTransform *= Matrix4Row::CreateFromQuaternion(rotation);
        mWorldTransform *= Matrix4Row::CreateTranslation(location);
        mDirty = false;
    }
};
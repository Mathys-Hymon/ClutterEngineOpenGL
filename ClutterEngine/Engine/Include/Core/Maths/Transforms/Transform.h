#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Quaternion.h>
#include <Core/Maths/Matrix/Matrix4Row.h>
#include <Core/Maths/Maths.h>

class CLUTTER_API Transform
{
    Vector3 location = { 0, 0, 0 };
    Vector3 scale = { 1, 1, 1 };

    Quaternion rotation {0, 0, 0, 0};
    Matrix4Row mWorldTransform;

public:

    Transform() { ComputeWorldTransform(); };
    Transform(Vector3 pLocation, Vector3 pScale, Quaternion pRotation) : location(pLocation), scale(pScale), rotation(pRotation) { ComputeWorldTransform(); };

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
        ComputeWorldTransform();
    }

    void SetLocation(Vector2 newLocation)
    {
        location = newLocation;
        ComputeWorldTransform();
    }

    void SetRotation(Quaternion newRotation)
    {
        rotation = newRotation;
        ComputeWorldTransform();
    }

    void SetRotation(float newRotation)
    {
        rotation = newRotation;
        ComputeWorldTransform();
    }

    void SetScale(Vector3 newScale)
    {
        scale = newScale;
        ComputeWorldTransform();
    }

    void SetScale(Vector2 newScale)
    {
        scale = newScale;
        ComputeWorldTransform();
    }

    Transform operator+(const Transform& q) const
    {
        return { location + q.location, scale + q.scale, rotation + q.rotation };
    }

    Vector3 Location() const { return location; };
    Vector3 Scale() const { return scale; };
    Quaternion Rotation() const { return rotation; };
    Matrix4Row GetWorldTransform() const { return mWorldTransform; }

    //friend Transform operator+(Transform left, Transform right)
    //{
    //    return { left.location + right.location, left.scale * right.scale, left.rotation + right.rotation };
    //}

    void ComputeWorldTransform()
    {
        mWorldTransform =  Matrix4Row::CreateScale(scale);
        mWorldTransform *= Matrix4Row::CreateRotationX(rotation.x);
        mWorldTransform *= Matrix4Row::CreateRotationY(rotation.y);
        mWorldTransform *= Matrix4Row::CreateRotationZ(rotation.z);
        mWorldTransform *= Matrix4Row::CreateTranslation(location);
    }

};
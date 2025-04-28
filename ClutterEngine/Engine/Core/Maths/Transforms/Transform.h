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


    Vector3 Right() const { return Vector3::Transform(Vector3::unitX, rotation); }
    Vector3 Up() const { return Vector3::Transform(Vector3::unitY, rotation); }
    Vector3 Forward() const { return Vector3::Transform(Vector3::unitZ, rotation); }



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

    void SetRotation(Vector3 newRotation)
    {
        rotation = Quaternion::Concatenate(Quaternion::Identity, Quaternion::FromEuler(newRotation));
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
    Vector3 EulerRotation() const { return rotation.QuaternionToEuler(); };
    Matrix4Row GetMat4Transform() 
    { 
        if (mDirty)  ComputeWorldTransform();
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
#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Quaternion.h>
#include <Core/Maths/Matrix/Matrix4Row.h>
#include <Core/Maths/Maths.h>

/**
 * @brief Represents a 3D transformation including translation, rotation, and scale.
 */
class CLUTTER_API Transform
{
    Vector3 location = { 0, 0, 0 };      ///< Position in world space.
    Vector3 scale = { 1, 1, 1 };         ///< Scale in each axis.

    Quaternion rotation {0, 0, 0, 1};    ///< Rotation as a quaternion.
    Matrix4Row mWorldTransform;          ///< Cached world transformation matrix.

    bool mDirty = true;                  ///< Indicates if the transform needs to be recomputed.

public:

    /**
     * @brief Default constructor. Initializes to identity transform.
     */
    Transform() { mDirty = true; };

    /**
     * @brief Constructs a transform with given location, scale, and rotation.
     * @param pLocation The position.
     * @param pScale The scale.
     * @param pRotation The rotation as a quaternion.
     */
    Transform(Vector3 pLocation, Vector3 pScale, Quaternion pRotation) : location(pLocation), scale(pScale), rotation(pRotation) { mDirty = true; };

    /**
     * @brief Gets the right direction vector in world space.
     * @return The right vector.
     */
    Vector3 Right() const { return Vector3::Transform(Vector3::Right, rotation); }

    /**
     * @brief Gets the up direction vector in world space.
     * @return The up vector.
     */
    Vector3 Up() const { return Vector3::Transform(Vector3::Up, rotation); }

    /**
     * @brief Gets the forward direction vector in world space.
     * @return The forward vector.
     */
    Vector3 Forward() const { return Vector3::Transform(Vector3::Forward, rotation); }

    /**
     * @brief Transforms a local position to world space.
     * @param localPosition The local position.
     * @return The transformed world position.
     */
    Vector3 TransformPosition(const Vector3& localPosition) const
    {
        Vector3 scaled = localPosition * scale;
        Vector3 rotated = Vector3::Transform(scaled, rotation);
        return rotated + location;
    }

    /**
     * @brief Transforms a world position to local space.
     * @param worldPosition The world position.
     * @return The transformed local position.
     */
    Vector3 InverseTransformPosition(const Vector3& worldPosition) const
    {
        Vector3 delta = worldPosition - location;
        Quaternion invRot = rotation.Inverse();
        Vector3 unrotated = Vector3::Transform(delta, invRot);
        return unrotated / scale;
    }

    /**
     * @brief Sets the location.
     * @param newLocation The new location.
     */
    void SetLocation(Vector3 newLocation)
    {
        location = newLocation;
        mDirty = true;
    }

    /**
     * @brief Sets the location using a Vector2.
     * @param newLocation The new location.
     */
    void SetLocation(Vector2 newLocation)
    {
        location = newLocation;
        mDirty = true;
    }

    /**
     * @brief Sets the rotation using a quaternion.
     * @param newRotation The new rotation.
     */
    void SetRotation(Quaternion newRotation)
    {
        newRotation.Normalize();
        rotation = newRotation;
        mDirty = true;
    }

    /**
     * @brief Sets the rotation using Euler angles.
     * @param newRotation The new rotation as Euler angles.
     */
    void SetRotation(Vector3 newRotation)
    {
        rotation = Quaternion::Concatenate(Quaternion::Identity, Quaternion::FromEuler(newRotation));
        mDirty = true;
    }

    /**
     * @brief Adds a rotation using Euler angles.
     * @param newRotation The rotation to add as Euler angles.
     */
    void AddRotation(Vector3 newRotation)
    {
        Quaternion additionalRotation = Quaternion::FromEuler(newRotation);
        rotation = Quaternion::Concatenate(rotation, additionalRotation);
        rotation.Normalize();
        mDirty = true;
    }

    /**
     * @brief Sets the rotation using a float (implementation dependent).
     * @param newRotation The new rotation.
     */
    void SetRotation(float newRotation)
    {
        rotation = newRotation;
        rotation.Normalize();
        mDirty = true;
    }

    /**
     * @brief Sets the scale.
     * @param newScale The new scale.
     */
    void SetScale(Vector3 newScale)
    {
        scale = newScale;
        mDirty = true;
    }

    /**
     * @brief Sets the scale using a Vector2.
     * @param newScale The new scale.
     */
    void SetScale(Vector2 newScale)
    {
        scale = newScale;
        mDirty = true;
    }

    /**
     * @brief Combines this transform with another.
     * @param q The other transform.
     * @return The combined transform.
     */
    Transform operator+(const Transform& q) const
    {
        return { location + q.location, scale * q.scale, Quaternion::Concatenate(q.rotation, rotation) };
    }

    /**
     * @brief Gets the current location.
     * @return The location.
     */
    Vector3 Location() const { return location; };

    /**
     * @brief Gets the current scale.
     * @return The scale.
     */
    Vector3 Scale() const { return scale; };

    /**
     * @brief Gets the current rotation as a quaternion.
     * @return The rotation.
     */
    Quaternion Rotation() const { return rotation; };

    /**
     * @brief Gets the current rotation as Euler angles.
     * @return The Euler angles.
     */
    Vector3 EulerRotation() const { return rotation.QuaternionToEuler(); };

    /**
     * @brief Gets the 4x4 transformation matrix.
     * @return The transformation matrix.
     */
    Matrix4Row GetMat4Transform() 
    { 
        if (mDirty)  ComputeWorldTransform();
        return mWorldTransform; 
    };

    /**
     * @brief Computes the world transformation matrix from location, rotation, and scale.
     */
    void ComputeWorldTransform()
    {
        mWorldTransform = Matrix4Row::CreateScale(scale);
        mWorldTransform *= Matrix4Row::CreateFromQuaternion(rotation);
        mWorldTransform *= Matrix4Row::CreateTranslation(location);
        mDirty = false;
    }
};

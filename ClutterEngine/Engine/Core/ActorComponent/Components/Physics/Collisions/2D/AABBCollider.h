#pragma once
#include <Core/ActorComponent/Components/Physics/Collisions/ColliderComponent.h>
#include <array>

namespace clt
{
    class CircleCollider;
    
    /**
    * @brief A class representing an Axis-Aligned Bounding Box (AABB) collider.
    */
    class CLUTTER_API AABBCollider : public ColliderComponent
    {
        /**
        * @brief Checks for collision between two AABB colliders.
        * @param pOther The other AABB collider.
        * @param outResult The result of the collision check.
        * @return True if a collision is detected, false otherwise.
        */
        bool CheckAABBvsAABB(AABBCollider* pOther, HitResult& outResult) const;

        /**
        * @brief Gets the transformed points of the AABB collider.
        * @return An array of four transformed points.
        */
        std::array<Vector2, 4> GetTransformedPoints() const;

        /**
        * @brief Checks for collision between an AABB collider and a circle collider.
        * @param pOther The circle collider.
        * @param outResult The result of the collision check.
        * @return True if a collision is detected, false otherwise.
        */
        bool CheckAABBvsCircle(CircleCollider* pOther, HitResult& outResult) const;

    public:

        Vector2 mBoxExtend; ///< The extension of the bounding box.
        /**
        * @brief Constructs an AABBCollider with the specified box extension.
        * @param pBoxExtend The extension of the bounding box.
        */
        AABBCollider(Vector2 pBoxExtend = {32,32});
        /**
        * @brief Constructs an AABBCollider with the specified box extension.
        * @param pBoxExtend The extension of the bounding box.
        */
        AABBCollider(float pBoxExtend);

        /**
        * @brief Default destructor.
        */
        ~AABBCollider() = default;

        /**
        * @brief Checks for collision with another collider.
        * @param pOther The other collider.
        * @param outResult The result of the collision check.
        * @return True if a collision is detected, false otherwise.
        */
        bool CheckCollision(ColliderComponent* pOther, HitResult& outResult) const override;

        friend CircleCollider;
    };
}
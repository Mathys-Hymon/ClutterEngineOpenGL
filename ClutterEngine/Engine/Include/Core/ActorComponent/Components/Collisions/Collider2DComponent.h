#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/ActorComponent/Components/Collisions/HitResult.h>

namespace clt
{
	/**
  * @class Collider2DComponent
  * @brief A component that handles 2D collision detection.
  */
	class CLUTTER_API Collider2DComponent : public Component
	{
	public:
		/**
   * @enum Type
   * @brief The type of the collider.
   */
		enum class Type { AABB, Circle };

	protected:
		/**
   * @brief Sets the owner of this component.
   * @param pOwner Pointer to the actor that owns this component.
   */
		virtual void SetOwner(Actor* pOwner) override;

		bool mTrigger = false; ///< Indicates if the collider is a trigger.
		Type mType; ///< The type of the collider.

	public:

		float mFriction;
		float mBounciness;
		/**
   * @brief Constructor for Collider2DComponent.
   */
		Collider2DComponent();

		/**
   * @brief Destructor for Collider2DComponent.
   */
		~Collider2DComponent() = default;

		/**
   * @brief Checks for collision with another collider.
   * @param pOther Pointer to the other collider.
   * @param outResult The result of the collision.
   * @return True if a collision occurred, false otherwise.
   */
		virtual bool CheckCollision(Collider2DComponent* pOther, hitResult2D& outResult) const = 0;

		/**
   * @brief Gets the type of the collider.
   * @return The type of the collider.
   */
		Type GetType() const { return mType; };

		/**
   * @brief Checks if the collider is a trigger.
   * @return True if the collider is a trigger, false otherwise.
   */
		bool IsTrigger() const { return mTrigger; };
	};
}
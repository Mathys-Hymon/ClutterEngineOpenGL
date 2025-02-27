#pragma once
#include <Core/ActorComponent/Component.h>

namespace clt
{
	/**
  * @brief A 2D rigid body component for physics simulation.
  */
	class CLUTTER_API RigidBody2D : public Component
	{
		Vector2 mVelocity; ///< The velocity of the rigid body.
		Vector2 mAcceleration; ///< The acceleration of the rigid body.

	public:

		float mGravityScale; ///< The scale of gravity applied to the rigid body.
		float mGroundFriction;
		float mAirFriction;
		/**
   * @brief Constructs a RigidBody2D with an optional update order.
   * @param pUpdadeOrder The update order of the component.
   */
		RigidBody2D(float pMass = 1, int pUpdadeOrder = 0);

		/**
   * @brief Default destructor.
   */
		~RigidBody2D() = default;

		float mMass; ///< The mass of the rigid body.
		float mAngularVelocity; ///< The angular velocity of the rigid body.

		bool mSimulatePhysics = false; ///< Flag to simulate physics.
		bool mIsKinematic = false; ///< Flag to set the rigid body as kinematic.
		bool mIsGrounded = false; ///< Flag to check if the rigid body is grounded.
		bool mCanStepOn = true;

		/**
   * @brief Sets the owner of the component.
   * @param pOwner The owner actor.
   */
		virtual void SetOwner(Actor* pOwner) override;

		/**
   * @brief Adds a force to the rigid body.
   * @param pForce The force to add.
   */
		void AddForce(const Vector2& pForce);

		/**
   * @brief Sets the velocity of the rigid body.
   * @param pVelocity The new velocity.
   */
		void SetVelocity(Vector2 pVelocity) { mVelocity = pVelocity; };

		/**
   * @brief Adds to the current velocity of the rigid body.
   * @param pVelocity The velocity to add.
   */
		void AddVelocity(Vector2 pVelocity) { mVelocity += pVelocity; };

		/**
   * @brief Sets the gravity scale of the rigid body.
   * @param pGravityScale The new gravity scale.
   */
		void SetGravityScale(float pGravityScale)  { mGravityScale = pGravityScale; };

		/**
   * @brief Gets the current velocity of the rigid body.
   * @return The current velocity.
   */
		Vector2 GetVelocity() const { return mVelocity; };

		/**
   * @brief Gets the current gravity scale of the rigid body.
   * @return The current gravity scale.
   */
		float GetGravityScale()  const { return mGravityScale;  };
	};
}
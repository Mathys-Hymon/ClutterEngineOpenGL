#pragma once
#include <Core/ActorComponent/Component.h>

namespace clt
{
	/**
  * @brief A rigid body component for physics simulation.
  */
	class Physics;
	class CLUTTER_API RigidBody : public Component
	{
		Vector3 mVelocity; ///< The velocity of the rigid body.
		Vector3 mAcceleration; ///< The acceleration of the rigid body.
		Vector3 mAngularVelocity; ///< The angular velocity of the rigid body.
		Vector3 mTorque; ///< The torque applied to the rigid body.

		/**
   * @brief Updates the rotation of the rigid body.
   * @param deltaTime The time elapsed since the last update.
   */
		void UpdateRotation(float deltaTime);

	public:

		float mGravityScale; ///< The scale of gravity applied to the rigid body.
		/**
   * @brief Constructs a RigidBody2D with an optional update order.
   * @param pMass The mass of the rigid body.
   * @param pUpdadeOrder The update order of the component.
   */
		RigidBody(float pMass = 1, int pUpdadeOrder = 0);

		/**
   * @brief Default destructor.
   */
		~RigidBody() = default;

		float mMass; ///< The mass of the rigid body.
		float mInertia; ///< The inertia of the rigid body.

		bool mSimulatePhysics = false; ///< Flag to simulate physics.
		bool mIsKinematic = false; ///< Flag to set the rigid body as kinematic.
		bool mIsGrounded = false; ///< Flag to check if the rigid body is grounded.
		bool mCanStepOn = true; ///< Flag to check if the rigid body can step on.
		bool mLockRotation = true; ///< Flag to lock rotation.

		/**
   * @brief Sets the owner of the component.
   * @param pOwner The owner actor.
   */
		virtual void SetOwner(Actor* pOwner) override;

		/**
   * @brief Adds a force to the rigid body.
   * @param pForce The force to add.
   */
		void AddForce(const Vector3& pForce);

		/**
   * @brief Sets the velocity of the rigid body.
   * @param pVelocity The new velocity.
   */
		void SetVelocity(Vector3 pVelocity) { mVelocity = pVelocity; };

		/**
   * @brief Adds to the current velocity of the rigid body.
   * @param pVelocity The velocity to add.
   */
		void AddVelocity(Vector3 pVelocity) { mVelocity += pVelocity; };

		void AddVelocity(Vector2 pVelocity) { mVelocity += pVelocity; };

		/**
   * @brief Sets the angular velocity of the rigid body.
   * @param pVel The new angular velocity.
   */
		void SetAngularVelocity(Vector3 pVel) { mAngularVelocity = pVel; };

		/**
   * @brief Adds to the current angular velocity of the rigid body.
   * @param pVel The angular velocity to add.
   */
		void AddAngularVelocity(Vector3 pVel) { mAngularVelocity += pVel; };

		/**
   * @brief Sets the gravity scale of the rigid body.
   * @param pGravityScale The new gravity scale.
   */
		void SetGravityScale(float pGravityScale)  { mGravityScale = pGravityScale; };

		/**
   * @brief Gets the current velocity of the rigid body.
   * @return The current velocity.
   */
		Vector3 GetVelocity() const { return mVelocity; };

		/**
   * @brief Gets the current gravity scale of the rigid body.
   * @return The current gravity scale.
   */
		float GetGravityScale()  const { return mGravityScale;  };

		friend Physics;
	};

}
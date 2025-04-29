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
		Vector3 mForce;


		float mMass; ///< The mass of the rigid body.
		float mInvMass;  ///< The inverse mass of the rigid body.
		Vector3 mInertia; ///< The inertia of the rigid body.
		Vector3 mInvInertia; ///< The inverse inertia of the rigid body.

		bool mSimulatePhysics = true; ///< Flag to simulate physics.
		bool mIsKinematic = false; ///< Flag to set the rigid body as kinematic.
		bool mIsGrounded = false; ///< Flag to check if the rigid body is grounded.
		bool mCanStepOn = true; ///< Flag to check if the rigid body can step on.
		bool mLockRotation = false; ///< Flag to lock rotation.

		/**
   * @brief Updates the rotation of the rigid body.
   * @param deltaTime The time elapsed since the last update.
   */
		void UpdateRotation(float deltaTime);
		void CalculateInertia();

		void ApplyForces(float dt);

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

		/**
   * @brief Sets the owner of the component.
   * @param pOwner The owner actor.
   */
		virtual void SetOwner(Actor* pOwner) override;

		/**
   * @brief Sets the velocity of the rigid body.
   * @param pVelocity The new velocity.
   */
		void SetVelocity(const Vector3& pVelocity) { mVelocity = pVelocity; };

		/**
   * @brief Adds to the current velocity of the rigid body.
   * @param pVelocity The velocity to add.
   */
		void AddVelocity(const Vector3& pVelocity) { mVelocity += pVelocity; };

		void AddVelocity(const Vector2& pVelocity) { mVelocity += pVelocity; };

		void AddForce(const Vector3& pForce) { mForce += pForce; };

		void AddTorque(const Vector3& pTorque) { mTorque += pTorque; };

		/**
   * @brief Sets the angular velocity of the rigid body.
   * @param pVel The new angular velocity.
   */
		void SetAngularVelocity(const Vector3& pVel) { mAngularVelocity = pVel; };

		/**
   * @brief Adds to the current angular velocity of the rigid body.
   * @param pVel The angular velocity to add.
   */
		void AddAngularVelocity(const Vector3& pVel) { mAngularVelocity += pVel; };

		void AddAngularImpulse(const Vector3& pImpulse);

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

		Vector3 GetAngularVelocity() const { return mAngularVelocity; };

		/**
   * @brief Gets the current gravity scale of the rigid body.
   * @return The current gravity scale.
   */
		float GetGravityScale()  const { return mGravityScale;  };

		bool IsGrounded() const { return mIsGrounded; };

		bool SimulatePhysics() const { return mSimulatePhysics; };

		bool IsKinematic() const { return mIsKinematic; };

		void SetSimulate(bool simulate = true) { mSimulatePhysics = simulate; };

        void SetMass(float mass) 
		{ 
			mMass = mass; 
			mInvMass = (mass != 0.0f) ? 1.0f / mass : 0.0f; 
			CalculateInertia();
		};

		float GetMass() const { return mMass; };
		float GetInvMass() const { return mInvMass; };

		Vector3 GetInertia() const { return mInertia; };
		Vector3 GetInvInertia() const { return mInvInertia; };

		void LockRotation(bool lock = true) { mLockRotation = lock; };

		bool IsRotationLocked() const { return mLockRotation; };

		friend Physics;
	};

}
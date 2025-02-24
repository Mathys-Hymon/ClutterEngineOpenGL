#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/Collisions/Collider2DComponent.h>
#include <Core/ActorComponent/Components/Physics/RigidBody2D.h>
#include <Physics/Collision/CollisionEvent.h>

namespace clt
{
	/**
  * @brief The Physics class handles the physics simulation, including collision detection and resolution.
  */
	class CLUTTER_API Physics
	{
		std::unordered_map<Collider2DComponent*, CollisionEvent*> mColliderEvent; ///< Maps colliders to their collision events.
		std::vector<Collider2DComponent*> mColliders; ///< List of all colliders in the simulation.
		std::vector<RigidBody2D*> mRigidbody; ///< List of all rigid bodies in the simulation.

		Vector2 mGravity; ///< The gravity vector applied to all rigid bodies.

		std::vector<hitResult> mCurrentFrameCollisions; ///< Collisions detected in the current frame.
		std::vector<hitResult> mPreviousFrameCollisions; ///< Collisions detected in the previous frame.

		/**
   * @brief Checks for collisions between colliders.
   */
		void CheckCollisions();

		/**
   * @brief Resolves detected collisions.
   */
		void ResolveCollisions();

		/**
   * @brief Dispatches collision events to listeners.
   */
		void DispatchEvents();

	public:
		/**
   * @brief Constructs a new Physics object.
   */
		Physics();

		/**
   * @brief Destroys the Physics object.
   */
		~Physics();

		/**
   * @brief Adds a collider to the simulation.
   * @param pCollider The collider to add.
   */
		void AddCollider(Collider2DComponent* pCollider);

		/**
   * @brief Removes a collider from the simulation.
   * @param pCollider The collider to remove.
   */
		void RemoveCollider(Collider2DComponent* pCollider);

		/**
   * @brief Adds a rigid body to the simulation.
   * @param pRigidbody The rigid body to add.
   */
		void AddRigidbody(RigidBody2D* pRigidbody);

		/**
   * @brief Removes a rigid body from the simulation.
   * @param pRigidbody The rigid body to remove.
   */
		void RemoveRigidBody(RigidBody2D* pRigidbody);

		/**
   * @brief Subscribes a listener to collision events for a specific collider.
   * @param pCollider The collider to subscribe to.
   * @param pListener The listener to notify of collision events.
   */
		void SubscribeTo(Collider2DComponent* pCollider, ICollisionListener* pListener);

		/**
   * @brief Updates the physics simulation.
   */
		void Update();
	};
}
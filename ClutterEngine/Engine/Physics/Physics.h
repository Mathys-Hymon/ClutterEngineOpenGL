#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/Collisions/ColliderComponent.h>
#include <Core/ActorComponent/Components/Physics/RigidBody.h>
#include <Physics/Collision/CollisionEvent.h>
#include <set>

namespace clt
{
	/**
  * @brief The Physics class handles the physics simulation, including collision detection and resolution.
  */
	class CLUTTER_API Physics
	{
		std::unordered_map<ColliderComponent*, CollisionEvent*> mColliderEvent; ///< Maps colliders to their collision events.
		std::vector<ColliderComponent*> mColliders; ///< List of all colliders in the simulation.

		std::vector<RigidBody*> mRigidbody; ///< List of all rigid bodies in the simulation.

		Vector3 mGravity; ///< The gravity vector applied to all rigid bodies.

		std::set<std::pair<ColliderComponent*, ColliderComponent*>> mPreviousCollisions;
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
		~Physics() = default;

		bool LineTrace(Vector3 start, Vector3 direction, float maxDistance, raycastHit& hit, bool debugPersistant = false, Actor* self = nullptr);

		void AddCollider(ColliderComponent* pCollider);

		void RemoveCollider(ColliderComponent* pCollider);

		/**
   * @brief Adds a rigid body to the simulation.
   * @param pRigidbody The rigid body to add.
   */
		void AddRigidbody(RigidBody* pRigidbody);

		/**
   * @brief Removes a rigid body from the simulation.
   * @param pRigidbody The rigid body to remove.
   */
		void RemoveRigidBody(RigidBody* pRigidbody);

		/**
   * @brief Subscribes a listener to collision events for a specific collider.
   * @param pCollider The collider to subscribe to.
   * @param pListener The listener to notify of collision events.
   */
		void SubscribeTo(ColliderComponent* pCollider, ICollisionListener* pListener);

		/**
   * @brief Updates the physics simulation.
   */
		void Update();
	};
}
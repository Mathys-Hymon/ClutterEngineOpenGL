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
		/**
   * @brief Maps colliders to their collision events.
   */
		std::unordered_map<ColliderComponent*, CollisionEvent*> mColliderEvent;

		/**
   * @brief List of all colliders in the simulation.
   */
		std::vector<ColliderComponent*> mColliders;

		/**
   * @brief List of all rigid bodies in the simulation.
   */
		std::vector<RigidBody*> mRigidbody;

		/**
   * @brief The gravity vector applied to all rigid bodies.
   */
		Vector3 mGravity;

		/**
   * @brief Set of collider pairs that collided in the previous frame.
   */
		std::set<std::pair<ColliderComponent*, ColliderComponent*>> mPreviousCollisions;

		/**
   * @brief Collisions detected in the current frame.
   */
		std::vector<hitResult> mCurrentFrameCollisions;

		/**
   * @brief Collisions detected in the previous frame.
   */
		std::vector<hitResult> mPreviousFrameCollisions;

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

		/**
   * @brief Performs a line trace (raycast) in the physics world.
   * @param start The starting point of the trace.
   * @param direction The direction of the trace.
   * @param maxDistance The maximum distance to trace.
   * @param hit The result of the trace if a hit occurs.
   * @param debugPersistant Whether to persist debug visualization.
   * @param self The actor to ignore during the trace.
   * @return True if the trace hit something, false otherwise.
   */
		bool LineTrace(Vector3 start, Vector3 direction, float maxDistance, raycastHit& hit, bool debugPersistant = false, Actor* self = nullptr);

		/**
   * @brief Adds a collider to the simulation.
   * @param pCollider The collider to add.
   */
		void AddCollider(ColliderComponent* pCollider);

		/**
   * @brief Removes a collider from the simulation.
   * @param pCollider The collider to remove.
   */
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

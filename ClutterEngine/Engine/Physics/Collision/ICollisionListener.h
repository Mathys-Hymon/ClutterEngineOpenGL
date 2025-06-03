#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/Collisions/HitResult.h>

namespace clt
{
	/**
  * @brief Interface for receiving collision and trigger events from the physics engine.
  */
	class CLUTTER_API ICollisionListener
	{
	public :
		/**
   * @brief Virtual destructor for safe polymorphic use.
   */
		virtual ~ICollisionListener() = default;

		/**
   * @brief Called when a collision begins with this listener's collider.
   * @param collider The collider component involved in the collision.
   * @param result Detailed information about the collision.
   */
		virtual void OnCollisionEnter(ColliderComponent* collider, const hitResult& result) {};

		/**
   * @brief Called while a collision is ongoing with this listener's collider.
   * @param collider The collider component involved in the collision.
   * @param result Detailed information about the collision.
   */
		virtual void OnCollisionStay (ColliderComponent* collider, const hitResult& result) {};

		/**
   * @brief Called when a collision ends with this listener's collider.
   * @param collider The collider component involved in the collision.
   * @param result Detailed information about the collision.
   */
		virtual void OnCollisionExit (ColliderComponent* collider, const hitResult& result) {};

		/**
   * @brief Called when a trigger event begins with this listener's collider.
   * @param collider The collider component involved in the trigger.
   * @param result Detailed information about the trigger event.
   */
		virtual void OnTriggerEnter(ColliderComponent* collider, const hitResult& result) {};

		/**
   * @brief Called while a trigger event is ongoing with this listener's collider.
   * @param collider The collider component involved in the trigger.
   * @param result Detailed information about the trigger event.
   */
		virtual void OnTriggerStay (ColliderComponent* collider, const hitResult& result) {};

		/**
   * @brief Called when a trigger event ends with this listener's collider.
   * @param collider The collider component involved in the trigger.
   * @param result Detailed information about the trigger event.
   */
		virtual void OnTriggerExit (ColliderComponent* collider, const hitResult& result) {};
	};
}

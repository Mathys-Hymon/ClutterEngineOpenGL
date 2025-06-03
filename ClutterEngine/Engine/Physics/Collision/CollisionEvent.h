#pragma once
#include <Physics/Collision/ICollisionListener.h>
#include <vector>

namespace clt
{
	/**
  * @brief Manages collision event notifications and listener subscriptions.
  */
	class CLUTTER_API CollisionEvent
	{
		/**
   * @brief List of registered collision listeners.
   */
		std::vector<ICollisionListener*> mListeners;

	public:
		/**
   * @brief Default constructor.
   */
		CollisionEvent() = default;

		/**
   * @brief Destructor.
   */
		~CollisionEvent();

		/**
   * @brief Subscribes a listener to collision events.
   * @param pListener Pointer to the listener to subscribe.
   */
		void Subscribe(ICollisionListener* pListener);

		/**
   * @brief Unsubscribes a listener from collision events.
   * @param pListener Pointer to the listener to unsubscribe.
   */
		void UnSubscribe(ICollisionListener* pListener);

		/**
   * @brief Notifies listeners of a collision enter event.
   * @param collider The collider component involved in the event.
   * @param result The collision hit result.
   */
		void NotifyEnter(ColliderComponent* collider, hitResult& result);

		/**
   * @brief Notifies listeners of a collision stay event.
   * @param collider The collider component involved in the event.
   * @param result The collision hit result.
   */
		void NotifyStay(ColliderComponent* collider, hitResult& result);

		/**
   * @brief Notifies listeners of a collision exit event.
   * @param collider The collider component involved in the event.
   * @param result The collision hit result.
   */
		void NotifyExit(ColliderComponent* collider, hitResult& result);

		/**
   * @brief Notifies listeners of a trigger enter event.
   * @param collider The collider component involved in the event.
   * @param result The collision hit result.
   */
		void TriggerEnter(ColliderComponent* collider, hitResult& result);

		/**
   * @brief Notifies listeners of a trigger stay event.
   * @param collider The collider component involved in the event.
   * @param result The collision hit result.
   */
		void TriggerStay(ColliderComponent* collider, hitResult& result);

		/**
   * @brief Notifies listeners of a trigger exit event.
   * @param collider The collider component involved in the event.
   * @param result The collision hit result.
   */
		void TriggerExit(ColliderComponent* collider, hitResult& result);
	};
}

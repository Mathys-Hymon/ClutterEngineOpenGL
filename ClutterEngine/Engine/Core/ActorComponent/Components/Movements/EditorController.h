#pragma once
#include <Core/ActorComponent/Components/Movements/PlayerController.h>

namespace clt
{
	class CLUTTER_API EditorController : public PlayerController
	{
		Vector2 mWorldRotation;
		float mMinSpeed;
		float mMaxSpeed;

		float mActualSpeed;

	public:
		EditorController(float pMouseSpeed = 1);
		~EditorController() = default;

		/**
 * @brief Handles player movement in a given direction.
 * @param pDirection The direction vector for movement.
 */
		void Movement(Vector2 pDirection);

		void MoveVertically(float pDirection);

		void Rotation(Vector2 pRotation);
		void ChangeSpeed(float pOffset);

		virtual void OnCollisionEnter(ColliderComponent* collider, const HitResult& result) override {};
		virtual void OnCollisionStay(ColliderComponent* collider, const HitResult& result)  override {};
		virtual void OnCollisionExit(ColliderComponent* collider, const HitResult& result)  override {};

		virtual void OnTriggerEnter(ColliderComponent* collider, const HitResult& result)override {};
		virtual void OnTriggerStay(ColliderComponent* collider, const HitResult& result) override {};
		virtual void OnTriggerExit(ColliderComponent* collider, const HitResult& result) override {};
	};
}
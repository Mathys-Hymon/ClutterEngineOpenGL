#pragma once
#include <Core/ActorComponent/Components/Movements/PlayerController.h>

namespace clt
{
	class CLUTTER_API FPSController : public clt::PlayerController
	{
		float mRotationInertia;
		float mMovementInertia;

		float mRotationVelocity;
		Vector2 mMovementVelocity;

	public:

		FPSController(float mMouseSpeed = 1, float pRotationInertia = 0, float pMovementInertia = 0);
		~FPSController() = default;

		void RotateCamera(Vector2 movement);
		void Move(Vector2 movement);

		virtual void Update() override;

		virtual void OnCollisionEnter(ColliderComponent* collider, const hitResult& result) override {};
		virtual void OnCollisionStay(ColliderComponent* collider, const hitResult& result)  override {};
		virtual void OnCollisionExit(ColliderComponent* collider, const hitResult& result)  override {};

		virtual void OnTriggerEnter(ColliderComponent* collider, const hitResult& result) override {};
		virtual void OnTriggerStay(ColliderComponent* collider, const hitResult& result)  override {};
		virtual void OnTriggerExit(ColliderComponent* collider,  const hitResult& result)  override {};
	};
}
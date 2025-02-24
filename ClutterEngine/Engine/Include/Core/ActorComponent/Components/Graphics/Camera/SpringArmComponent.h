#pragma once
#include <Core/ActorComponent/Component.h>

namespace clt
{
	class CLUTTER_API SpringArmComponent : public Component
	{
		Actor* mCamera;

	public:
		float mLagSpeed;
		float mLagMaxDistance;

		float mRotationLagSpeed;

		Vector2 mCameraOffset;
		float mArmLength;

		SpringArmComponent(Actor* pCamera, float pLagSpeed = 3.0f, int pUpdateOrder = 0);
		~SpringArmComponent() = default;

		void Update() override;
	};
}
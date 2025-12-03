#pragma once
#include <Core/ActorComponent/Component.h>
#include "Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h"

namespace clt
{
	class CLUTTER_API SpringArmComponent : public Component
	{
		Actor* mCameraActor;
		CameraComponent* mCameraComponent;

	public:
		
		CLUTTER_CLASS(SpringArmComponent);
		
		void SetupProperties() override 
		{
			CPROPERTY(mLagSpeed, clt::PropMode::ReadWrite);
			CPROPERTY(mLagMaxDistance, clt::PropMode::ReadWrite);
			CPROPERTY(mRotationLagSpeed, clt::PropMode::ReadWrite);
			CPROPERTY(mCameraOffset, clt::PropMode::ReadWrite);
			CPROPERTY(mArmLength, clt::PropMode::ReadWrite);
		}
		
		float mLagSpeed;
		float mLagMaxDistance;

		float mRotationLagSpeed;

		Vector3 mCameraOffset;
		float mArmLength;

		SpringArmComponent(Actor* pCamera, float pLagSpeed = 3.0f, int pUpdateOrder = 0);
		SpringArmComponent(CameraComponent* camera, float pLagSpeed = 3.0f, int pUpdateOrder = 0);
		SpringArmComponent(float pLagSpeed = 3.0f, int pUpdateOrder = 0);
		~SpringArmComponent() = default;

		void Start() override;

		void Update() override;
	};
}
#include "pch.h"
#include <Core/ActorComponent/Components/Movements/EditorController.h>
#include <Input/Inputs.h>

using namespace clt;

EditorController::EditorController(float pMouseSpeed) : PlayerController(2), mMinSpeed(0.1f), mMaxSpeed(10.0f), mActualSpeed(1.0f)
{
	Inputs::Get().RegisterMouseCallback([this](Vector2 value) { this->Rotation(value); });

	Inputs::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "CameraMovement");
	Inputs::Get().MapKeysToAxis(EKey::LeftShift, EKey::LeftControl, "verticalMovement");

	Inputs::Get().RegisterMouseCallback([this](Vector2 value) { this->Rotation(value); });
	Inputs::Get().RegisterVectCallback("CameraMovement", [this](Vector2 value) { this->Movement(value); });
	Inputs::Get().RegisterAxisCallback("verticalMovement", [this](float value) { this->MoveVertically(value); });
	Inputs::Get().RegisterScrollCallback([this](float value) { this->ChangeSpeed(value); });

	mMaxAcceleration = 1;
	mMaxWalkSpeed = 5;
	mMouseSpeed = pMouseSpeed;
}

void EditorController::Movement(Vector2 pDirection)
{
	float dt = Timer::deltaTime;

	Vector3 forward = pDirection.y * mOwner->GetTransform().Forward() * dt;
	Vector3 right = pDirection.x * mOwner->GetTransform().Right() * dt;

	mOwner->AddActorLocationOffset((- forward + right) * mActualSpeed);
}

void EditorController::MoveVertically(float pDirection)
{
	Vector3 up = pDirection * mOwner->GetTransform().Up() * Timer::deltaTime;
	
	mOwner->AddActorLocationOffset(up * mActualSpeed);
}

void EditorController::ChangeSpeed(float pDirection)
{
	mActualSpeed = Maths::Clamp(mActualSpeed + (pDirection * 0.2f), mMinSpeed, mMaxSpeed);
}

void EditorController::Rotation(Vector2 pRotation)
{
	if (Inputs::Get().IsButtonPressed(EMouseButton::Right))
	{
		clt::Inputs::Get().SetShowMouseCursor(false);

		Vector3 up = pRotation.x * Vector3::Up;
		Vector3 right = -pRotation.y * GetWorldTransform().Right();

		mOwner->AddActorRotationOffset((up + right));
	}
	else clt::Inputs::Get().SetShowMouseCursor(true);
}

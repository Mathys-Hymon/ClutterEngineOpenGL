#include "pch.h"
#include <Core/ActorComponent/Components/Movements/EditorController.h>
#include <Input/Inputs.h>

using namespace clt;

EditorController::EditorController(float pMouseSpeed) : PlayerController(2)
{
	Inputs::Get().RegisterMouseCallback([this](Vector2 value) { this->Rotation(value); });

	Inputs::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "CameraMovement");
	Inputs::Get().MapKeysToAxis(EKey::LeftShift, EKey::LeftControl, "verticalMovement");

	Inputs::Get().RegisterMouseCallback([this](Vector2 value) { this->Rotation(value); });
	Inputs::Get().RegisterVectCallback("CameraMovement", [this](Vector2 value) { this->Movement(value); });
	Inputs::Get().RegisterAxisCallback("verticalMovement", [this](float value) { this->MoveVertically(value); });

	mMaxAcceleration = 1;
	mMaxWalkSpeed = 5;
	mMouseSpeed = pMouseSpeed;
}

void EditorController::Movement(Vector2 pDirection)
{
	float dt = Timer::deltaTime;

	Vector3 forward = pDirection.y * mOwner->GetTransform().Forward() * dt;
	Vector3 right = pDirection.x * mOwner->GetTransform().Right() * dt;

	mOwner->AddActorLocationOffset(-forward + right);
}

void EditorController::MoveVertically(float pDirection)
{
	Vector3 up = pDirection * mOwner->GetTransform().Up() * Timer::deltaTime;
	
	mOwner->AddActorLocationOffset(up);
}

void EditorController::Rotation(Vector2 pRotation)
{
	if (Inputs::Get().IsButtonPressed(EMouseButton::Right))
	{
		clt::Inputs::Get().SetShowMouseCursor(false);

		Vector3 up = pRotation.x * mOwner->GetTransform().Up();
		Vector3 right = -pRotation.y * mOwner->GetTransform().Right();

		mOwner->AddActorRotationOffset((up + right));

	}
	else clt::Inputs::Get().SetShowMouseCursor(true);
}

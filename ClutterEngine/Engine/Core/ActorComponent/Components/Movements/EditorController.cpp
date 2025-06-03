#include "pch.h"
#include <Core/ActorComponent/Components/Movements/EditorController.h>
#include <Input/Input.h>

using namespace clt;

EditorController::EditorController(float pMouseSpeed) : PlayerController(2)
{
	Input::Get().RegisterMouseCallback([this](Vector2 value) { this->Rotation(value); });

	Input::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "CameraMovement");
	Input::Get().MapKeysToAxis(EKey::LeftShift, EKey::LeftControl, "verticalMovement");

	Input::Get().RegisterMouseCallback([this](Vector2 value) { this->Rotation(value); });
	Input::Get().RegisterVectCallback("CameraMovement", [this](Vector2 value) { this->Movement(value); });
	Input::Get().RegisterAxisCallback("verticalMovement", [this](float value) { this->MoveVertically(value); });

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
	if (Input::Get().IsButtonPressed(EMouseButton::Right))
	{
		clt::Input::Get().SetShowMouseCursor(false);
		mOwner->AddActorRotationOffset((Vector3{ -pRotation.y, pRotation.x, 0 }));

	}
	else clt::Input::Get().SetShowMouseCursor(true);
}

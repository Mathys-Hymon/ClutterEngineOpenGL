#include "pch.h"
#include <Core/ActorComponent/Components/Movements/EditorController.h>
#include <Input/Input.h>

using namespace clt;

EditorController::EditorController()
{
	Input::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "CameraMovement");
	Input::Get().MapKeysToAxis(EKey::E, EKey::Q, "verticalMovement");
	Input::Get().RegisterMouseCallback([this](Vector2 value) { this->Rotation(value); });
	Input::Get().RegisterVectCallback("CameraMovement", [this](Vector2 value) { this->Movement(value); });
	Input::Get().RegisterAxisCallback("verticalMovement", [this](float value) {this->MoveVertically(value); });

	Input::Get().RegisterMouseCallback([this](Vector2 value) { this->Rotation(value); });
}

void EditorController::Movement(Vector2 pDirection)
{
	Vector3 forward = pDirection.y * mOwner->GetTransform().Forward();
	Vector3 right = pDirection.x * mOwner->GetTransform().Right();

	mOwner->AddActorLocationOffset(-forward + right);
}

void EditorController::MoveVertically(float pDirection)
{
	Vector3 up = pDirection * mOwner->GetTransform().Up();
}

void EditorController::Rotation(Vector2 pRotation)
{
	mOwner->AddActorRotationOffset((Vector3{ -pRotation.y, pRotation.x, 0 } *Timer::deltaTime) * 0.1f);
}

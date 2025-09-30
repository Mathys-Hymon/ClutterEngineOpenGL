#include "pch.h"
#include <Core/ActorComponent/Components/Movements/CameraController.h>
#include <Input/Inputs.h>

using namespace clt;

CameraController::CameraController(std::string pMovementCallback, std::string pVerticalMovementCallback, float pSpeed) : PlayerController(pSpeed)
{
	Inputs::Get().RegisterVectCallback(pMovementCallback, [this](Vector2 value) { this->Movement(value); });
	Inputs::Get().RegisterAxisCallback(pVerticalMovementCallback, [this](float value) { this->MoveVertically(value); });
	Inputs::Get().RegisterMouseCallback([this](Vector2 value) { this->Rotation(value); });
}

void CameraController::Movement(Vector2 pDirection)
{
	Vector3 forward = pDirection.y * mOwner->GetActorTransform().Forward();
	Vector3 right = pDirection.x * mOwner->GetActorTransform().Right();

	mOwner->AddActorLocationOffset( (- forward + right) * mMaxWalkSpeed);
}

void CameraController::MoveVertically(float pDirection)
{
	mOwner->AddActorLocationOffset({ 0, pDirection, 0 });
}

void CameraController::Rotation(Vector2 pRotation)
{
	mOwner->AddActorRotationOffset((Vector3{ -pRotation.y, pRotation.x, 0 } *Timer::deltaTime));
}

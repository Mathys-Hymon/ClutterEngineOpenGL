#include "pch.h"
#include <Core/ActorComponent/Components/Movements/CameraController.h>
#include <Input/Input.h>

using namespace clt;

CameraController::CameraController(std::string pMovementCallback, std::string pVerticalCallback, std::string pRotationCallback, float pSpeed) : PlayerController(pSpeed)
{
	Input::Get().RegisterAxisCallback(pMovementCallback, [this](Vector2 value) { this->Movement(value); });
	Input::Get().RegisterAxisCallback(pVerticalCallback, [this](float value) { this->MoveVertically(value); });
	Input::Get().RegisterAxisCallback(pRotationCallback, [this](Vector2 value) { this->Rotation(value); });
}

void CameraController::Movement(Vector2 pDirection)
{
	mOwner->AddActorLocationOffset({pDirection.x, 0, pDirection.y});
}

void CameraController::MoveVertically(float pDirection)
{
	mOwner->AddActorLocationOffset({ 0, pDirection, 0 });
}

void CameraController::Rotation(Vector2 pRotation)
{
	mOwner->SetActorRotation(pRotation);
}

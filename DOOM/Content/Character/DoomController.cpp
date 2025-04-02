#include "DoomController.h"

using namespace clt;

DoomController::DoomController() : PlayerController(2)
{
	clt::Input::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "PlayerMovement");
	clt::Input::Get().RegisterMouseCallback([this](Vector2 value) { this->RotateCamera(value); });
	clt::Input::Get().RegisterVectCallback("PlayerMovement", [this](Vector2 value) { this->Move(value); });
}

void DoomController::RotateCamera(Vector2 movement)
{
	mOwner->AddActorRotationOffset(movement.x);
}

void DoomController::Move(Vector2 movement)
{
}
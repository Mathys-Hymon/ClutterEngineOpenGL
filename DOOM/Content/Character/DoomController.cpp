#include "DoomController.h"

using namespace clt;

DoomController::DoomController() : PlayerController(2), mRotationVelocity(0.0f), mMovementVelocity(0)
{
	clt::Input::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "PlayerMovement");
	clt::Input::Get().RegisterMouseCallback([this](Vector2 value) { this->RotateCamera(value); });
	clt::Input::Get().RegisterVectCallback("PlayerMovement", [this](Vector2 value) { this->Move(value); });
	
	mMaxAcceleration = 0.65f;
	mMaxWalkSpeed = 2;
}

void DoomController::RotateCamera(Vector2 movement)
{
	mRotationVelocity += movement.x * Timer::deltaTime;

	mOwner->AddActorRotationOffset({0, mRotationVelocity, 0});

	if( mRotationVelocity != 0) mRotationVelocity *= 45 * Timer::deltaTime;
}

void DoomController::Move(Vector2 movement)
{
	mMovementVelocity += movement * mMaxAcceleration;
	mMovementVelocity.Clamp(-mMaxWalkSpeed, mMaxSprintSpeed);
}

void DoomController::Update()
{
	if (mMovementVelocity.x != 0)
	{
		mOwner->AddActorLocationOffset(mMovementVelocity.x * mOwner->getTransform().Right());
		mMovementVelocity.x *= 57 * Timer::deltaTime;
	}

	if (mMovementVelocity.y != 0)
	{
		mOwner->AddActorLocationOffset(-mMovementVelocity.y * mOwner->getTransform().Forward());
		mMovementVelocity.y *= 57 * Timer::deltaTime;
	}
}

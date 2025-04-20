#include "pch.h"
#include "FpsController.h"
#include <Input/Input.h>

using namespace clt;

FPSController::FPSController(float pMouseSpeed, float pRotationInertia, float pMovementInertia) : PlayerController(2),
mRotationVelocity(0.0f), mMovementVelocity(0), mRotationInertia(pRotationInertia), mMovementInertia(pMovementInertia)
{
	clt::Input::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "PlayerMovement");
	clt::Input::Get().RegisterMouseCallback([this](Vector2 value) { this->RotateCamera(value); });
	clt::Input::Get().RegisterVectCallback("PlayerMovement", [this](Vector2 value) { this->Move(value); });

	mMaxAcceleration = 0.65f;
	mMaxWalkSpeed = 2;
	mMouseSpeed = pMouseSpeed;
}

void FPSController::RotateCamera(Vector2 movement)
{
	if (mRotationInertia != 0)
	{
		mRotationVelocity += movement.x * mRotationInertia * Timer::deltaTime;

		mOwner->AddActorRotationOffset({ 0, mRotationVelocity, 0 });

		if (mRotationVelocity != 0) mRotationVelocity *= 0.9f;
	}
	else
	{
		mOwner->AddActorRotationOffset({ 0, (movement.x * mMouseSpeed.x * Timer::deltaTime), 0 });
	}
}

void FPSController::Move(Vector2 movement)
{
	mMovementVelocity += movement * mMaxAcceleration;
	mMovementVelocity.Clamp(-mMaxWalkSpeed, mMaxSprintSpeed);
}

void FPSController::Update()
{
	if (mMovementVelocity.x != 0)
	{
		mOwner->AddActorLocationOffset(mMovementVelocity.x * mOwner->GetTransform().Right());
		mMovementVelocity.x *= 57 * Timer::deltaTime;
	}

	if (mMovementVelocity.y != 0)
	{
		mOwner->AddActorLocationOffset(-mMovementVelocity.y * mOwner->GetTransform().Forward());
		mMovementVelocity.y *= 57 * Timer::deltaTime;
	}
}

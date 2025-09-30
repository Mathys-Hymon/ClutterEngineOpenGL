#include "pch.h"
#include "FpsController.h"
#include <Input/Inputs.h>

using namespace clt;

FPSController::FPSController(float pMouseSpeed, float pRotationInertia, float pMovementInertia) : PlayerController(2),
mRotationVelocity(0.0f), mMovementVelocity(0), mRotationInertia(pRotationInertia), mMovementInertia(pMovementInertia)
{
	clt::Inputs::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "PlayerMovement");
	clt::Inputs::Get().RegisterMouseCallback([this](Vector2 value) { this->RotateCamera(value); });
	clt::Inputs::Get().RegisterVectCallback("PlayerMovement", [this](Vector2 value) { this->Move(value); });

	mMaxAcceleration = 1;
	mMaxWalkSpeed = 5;
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
		mOwner->AddActorRotationOffset({ 0, (movement.x * mMouseSpeed.x), 0 });
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
		mOwner->AddActorLocationOffset(mMovementVelocity.x * mOwner->GetActorTransform().Right() * clt::Timer::deltaTime);
		mMovementVelocity.x = 0;
	}

	if (mMovementVelocity.y != 0)
	{
		mOwner->AddActorLocationOffset(-mMovementVelocity.y * mOwner->GetActorTransform().Forward() * clt::Timer::deltaTime);
		mMovementVelocity.y = 0;
	}
}

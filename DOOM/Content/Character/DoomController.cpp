#include "DoomController.h"
#include "DoomHUD.h"

using namespace clt;

DoomController::DoomController() : PlayerController(2), mRotationVelocity(0.0f), mMovementVelocity(0)
{
	clt::Input::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "PlayerMovement");
	clt::Input::Get().MapKeyToAction(EMouseButton::Left, "PlayerShoot");

	clt::Input::Get().RegisterActionCallback("PlayerShoot", [this] {this->Shoot(); });
	clt::Input::Get().RegisterMouseCallback([this](Vector2 value) { this->RotateCamera(value); });
	clt::Input::Get().RegisterVectCallback("PlayerMovement", [this](Vector2 value) { this->Move(value); });
	
	mMaxAcceleration = 0.65f;
	mMaxWalkSpeed = 2;
}

void DoomController::Start()
{
	GetOwner()->AddComponent<DoomHUD>();
}

void DoomController::RotateCamera(Vector2 movement)
{
	mRotationVelocity += movement.x * Timer::deltaTime;

	mOwner->AddActorRotationOffset({0, mRotationVelocity, 0});

	if( mRotationVelocity != 0) mRotationVelocity *= 1 - (Timer::deltaTime * 12);
}

void DoomController::Move(Vector2 movement)
{
	mMovementVelocity += movement * mMaxAcceleration;
	mMovementVelocity.Clamp(-mMaxWalkSpeed, mMaxSprintSpeed);
}

void DoomController::Shoot()
{
	mOwner->GetComponentOfType<DoomHUD>()->TriggerShoot();
}

void DoomController::Update()
{
	float movementReduction = 1 - (Timer::deltaTime * 5);
	if (mMovementVelocity.x != 0)
	{
		mOwner->AddActorLocationOffset(mMovementVelocity.x * mOwner->GetTransform().Right());
		mMovementVelocity.x *= movementReduction;
	}

	if (mMovementVelocity.y != 0)
	{
		mOwner->AddActorLocationOffset(-mMovementVelocity.y * mOwner->GetTransform().Forward());
		mMovementVelocity.y *= movementReduction;
	}
}

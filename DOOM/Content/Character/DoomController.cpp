#include "DoomController.h"
#include "DoomHUD.h"

using namespace clt;

DoomController::DoomController() : PlayerController(2), 
mRotationVelocity(0.0f), mMovementVelocity(0), mWeapon(Weapons::Pistol), mLife(100)
{
	clt::Input::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "PlayerMovement");
	clt::Input::Get().MapKeyToAction(EMouseButton::Left, "PlayerShoot");

	clt::Input::Get().RegisterActionCallback("PlayerShoot", [this] {this->Shoot(); });
	clt::Input::Get().RegisterMouseCallback([this](Vector2 value) { this->RotateCamera(value); });
	clt::Input::Get().RegisterVectCallback("PlayerMovement", [this](Vector2 value) { this->Move(value); });
	
	mMaxAcceleration = 25;
	mMaxWalkSpeed = 6;

	mWeaponAmmo =
	{
		{Weapons::Hand, 0},
		{Weapons::Pistol, 50},
		{Weapons::ShotGun, 25 }
	};
}

void DoomController::Start()
{

	GetOwner()->AddComponent<DoomHUD>();
	mHand = mOwner->GetComponentOfType<DoomHUD>()->GetCurrentWidget()->
		GetElement<AnimatorElement>("playerWeapon");
}

void DoomController::RotateCamera(Vector2 movement)
{
	mRotationVelocity += movement.x * 0.005f;

	mOwner->AddActorRotationOffset({0, mRotationVelocity, 0});

	if( mRotationVelocity != 0) mRotationVelocity *= 1 - (Timer::deltaTime * 12);
}

void DoomController::Move(Vector2 movement)
{
	mMovementVelocity += movement * mMaxAcceleration * clt::Timer::deltaTime;
	mMovementVelocity.Clamp(-mMaxWalkSpeed, mMaxWalkSpeed);

	if (movement.Length() != 0) mIsMoving = true;
	else mIsMoving = false;

	if (movement.x == 0) mMoveRight = false;
	else mMoveRight = true;

	if (movement.y == 0) mMoveForward = false;
	else mMoveForward = true;
}

void DoomController::Shoot()
{
	if (mWeaponAmmo[mWeapon] != 0)
	{
		if(mOwner->GetComponentOfType<DoomHUD>()->TriggerShoot(mWeaponAmmo[mWeapon] - 1)) mWeaponAmmo[mWeapon]--;
	}
}

void DoomController::GetHit()
{
	mLife -= 10;
	mOwner->GetComponentOfType<DoomHUD>()->UpdateLife(mLife);
}

void DoomController::Update()
{
	float dt = Timer::deltaTime;
	float movementReduction = 1 - (dt * 5);

	if (mMovementVelocity.x != 0)
	{
		mOwner->AddActorLocationOffset(mMovementVelocity.x * mOwner->GetTransform().Right() * dt);
		if(!mMoveRight) mMovementVelocity.x *= movementReduction;
	}

	if (mMovementVelocity.y != 0)
	{
		mOwner->AddActorLocationOffset(-mMovementVelocity.y * mOwner->GetTransform().Forward() * dt);
		if (!mMoveForward) mMovementVelocity.y *= movementReduction;
	}

	Vector2 handPos;

	if (mIsMoving) handPos = { Maths::Sin(Timer::GetTimeSinceLoad() * 4) * 300, -300 - 
(Maths::Cos(Timer::GetTimeSinceLoad() * 8) * 70) };
	else handPos = { 0,-300 };

	mHand->SetPosition(Vector2::VInterp(mHand->GetPosition(), handPos, dt, 4));
}

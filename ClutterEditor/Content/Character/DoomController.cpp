#include "DoomController.h"
#include "DoomHUD.h"

using namespace clt;

DoomController::DoomController() : PlayerController(2), 
mRotationVelocity(0.0f), mMovementVelocity(0), mWeapon(Weapons::Pistol), mLife(100), mDead(false)
{
	clt::Inputs::Get().MapKeysToVect(EKey::A, EKey::D, EKey::W, EKey::S, "PlayerMovement");
	clt::Inputs::Get().MapKeyToAction(EMouseButton::Left, "PlayerShoot");

	clt::Inputs::Get().RegisterActionCallback("PlayerShoot", [this] {this->Shoot(); });
	clt::Inputs::Get().RegisterMouseCallback([this](Vector2 value) { this->RotateCamera(value); });
	clt::Inputs::Get().RegisterVectCallback("PlayerMovement", [this](Vector2 value) { this->Move(value); });
	
	clt::Assets::Get().LoadAudio("Content/Resources/Audio/shoot.wav", "shoot", AudioCategory::SFX);
	
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
	if (!mDead)
	{
		mRotationVelocity += movement.x * 0.005f;

		mOwner->AddActorRotationOffset({ 0, mRotationVelocity, 0 });

		if (mRotationVelocity != 0) mRotationVelocity *= 1 - (Timer::deltaTime * 12);
	}
	else
	{
		mRotationVelocity = 0;
	}
}

void DoomController::Move(Vector2 movement)
{
	if (!mDead)
	{
		Vector3 dir = (mOwner->GetTransform().Right() * movement.x * mMaxAcceleration * clt::Timer::deltaTime) + (-mOwner->GetTransform().Forward() * movement.y * mMaxAcceleration * clt::Timer::deltaTime);

		clt::RigidBody* rb = mOwner->GetComponentOfType<clt::RigidBody>();

		rb->AddVelocity(dir);
		Vector3 vel = rb->GetVelocity();
		rb->SetVelocity(Vector3::Clamp(rb->GetVelocity(), -mMaxWalkSpeed, mMaxWalkSpeed));

		if (movement.Length() != 0) mIsMoving = true;
		else mIsMoving = false;
	}
	else
	{
		mIsMoving = false;
	}
}

void DoomController::Shoot()
{
	if (mWeaponAmmo[mWeapon] != 0 && !mDead)
	{
		if(mOwner->GetComponentOfType<DoomHUD>()->TriggerShoot(mWeaponAmmo[mWeapon] - 1)) mWeaponAmmo[mWeapon]--;
	}
}

void DoomController::GetHit()
{
	if (!mDead)
	{
		mLife -= 10;
		mOwner->GetComponentOfType<DoomHUD>()->UpdateLife(mLife);

		if (mLife <= 0)
		{
			mDead = true;
			mOwner->GetComponentOfType<clt::OBBCollider>()->SetBoxExtend(0.05f);
		}
	}
}

void DoomController::Update()
{
	float dt = Timer::deltaTime;
	float movementReduction = 1 - (dt * 5);

	Vector2 handPos;

	if (mIsMoving) handPos = { Maths::Sin(Timer::GetTimeSinceLoad() * 4) * 300, -300 - 
(Maths::Cos(Timer::GetTimeSinceLoad() * 8) * 70) };
	else handPos = { 0,-300 };

	mHand->SetPosition(Vector2::VInterp(mHand->GetPosition(), handPos, dt, 4));
}

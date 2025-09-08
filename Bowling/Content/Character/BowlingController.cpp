#include "BowlingController.h"

BowlingController::BowlingController() : PlayerController(), mMode(mode::movement), mRotation(-180), mShootForce(0), mSprite(nullptr), mResetTimer(0)
{
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/bowlingPreviewRot.png", "previewRotation");
	clt::Assets::Get().LoadTexture("Content/Resources/Sprites/bowlingPreview.png", "previewTrajectory");

	clt::Inputs::Get().MapKeysToAxis(EKey::A, EKey::D,"PlayerMovement");
	clt::Inputs::Get().MapKeyToAction(EKey::Space, "changeMod");

	
	clt::Inputs::Get().MapKeyToAction(EMouseButton::Left, "PlayerShoot", EInputState::Released);
	clt::Inputs::Get().RegisterActionCallback("PlayerShoot", [this] {this->Shoot(); });


	clt::Inputs::Get().MapKeyToAction(EMouseButton::Left, "PlayerCharge", EInputState::Held);
	clt::Inputs::Get().RegisterActionCallback("PlayerCharge", [this] {this->ChargeShoot(); });

	clt::Inputs::Get().RegisterAxisCallback("PlayerMovement", [this](float value) { this->Move(value); });
	clt::Inputs::Get().RegisterActionCallback("changeMod", [this] {this->ChangeMod(); });
}

void BowlingController::Start()
{
	mOwner->GetComponentOfType<clt::HUDComponent>()->CreateWidget<clt::UIPanel>("PlayerScreen");
	mSprite = mOwner->GetComponentOfType<clt::HUDComponent>()->GetCurrentWidget()->CreateElement<clt::SpriteElement>("preview", "previewTrajectory", 1, Vector2{ 0, -300 }, 50);

	mBall = mOwner->GetLevel()->GetActorOfType< BowlingBall>();

	mBall->GetComponentOfType<clt::RigidBody>()->SetSimulate(false);

}

void BowlingController::Move(float movement)
{

	if (mMode == mode::movement)
	{
		if (mRotation != -180)
		{
			Maths::Finterp(mRotation, -180, 3);
			mOwner->SetActorRotation({ 0, mRotation, 0 });
		}
		
		float locationX = Maths::Clamp(mOwner->GetActorLocation().x + -movement * clt::Timer::deltaTime, -2.5f, -0.5f);

		mOwner->SetActorLocation({ locationX, mOwner->GetActorLocation().y, mOwner->GetActorLocation().z });
	}
	else if (mMode == mode::rotation)
	{
		mRotation += movement * clt::Timer::deltaTime * 5;
		mRotation = Maths::Clamp(mRotation, -200.0f, 200.0f);
		mOwner->SetActorRotation({ 0, mRotation, 0});
	}
	
	if (movement != 0 && mMode != mode::shoot)
	{
		mBall->SetActorLocation((mOwner->GetActorLocation() - mOwner->GetTransform().Forward()) - Vector3{ 0,0.5,0 });
		mBall->GetComponentOfType<clt::RigidBody>()->SetSimulate(false);
	}
}

void BowlingController::ChangeMod()
{
	switch (mMode)
	{
	case BowlingController::mode::movement:
		mMode = mode::rotation;
		mSprite->SetTexture("previewRotation");
		break;
	case BowlingController::mode::rotation:
		mSprite->SetTexture("previewTrajectory");
		mMode = mode::movement;
		break;
	default:
		break;
	}
}

void BowlingController::ChargeShoot()
{
	if (mMode != mode::shoot)
	{
		mShootForce += clt::Timer::deltaTime;

		mShootForce = Maths::Clamp(mShootForce, 0.0f, 1.0f);
		mSprite->SetSize({ 1.0,mShootForce });
		mSprite->SetPosition({ 0.0f ,-600 + mShootForce * 300 });
		mBall->GetComponentOfType<clt::RigidBody>()->SetSimulate(false);

		mBall->SetActorLocation((mOwner->GetActorLocation() - mOwner->GetTransform().Forward()) - Vector3{ 0,0.5,0 });
	}
}

void BowlingController::Shoot()
{
	if (mMode != mode::shoot)
	{
		if (mBall)
		{
			mBall->GetComponentOfType<clt::RigidBody>()->SetSimulate(true);
			mBall->GetComponentOfType<clt::RigidBody>()->AddForce(mOwner->GetTransform().Forward() * mShootForce * -5000 * mBall->GetComponentOfType<clt::RigidBody>()->GetMass());
		}
		mShootForce = 0;
		mMode = mode::shoot;
		mSprite->mVisibility = false;
	}

}

void BowlingController::Update()
{
	auto& cam = *mOwner->GetComponentOfType<clt::CameraComponent>();
	if (mBall->GetActorLocation().z > 1 &&  mMode == mode::shoot)
	{
		mOwner->GetComponentOfType<clt::SpringArmComponent>()->SetWorldLocation({ 0, -0.6f, 8 });

	}

	if (mMode == mode::shoot)
	{
		cam.SetWorldRotation(Quaternion::LookAt(cam.GetWorldLocation(), mBall->GetActorLocation()));
	}
	else
	{
		cam.SetRelativeRotation(Vector3::Zero);
	}

	auto& rb = *mBall->GetComponentOfType<clt::RigidBody>();

	if (rb.SimulatePhysics() && (rb.GetVelocity().LengthSq() < 5 || !rb.IsGrounded()))
	{
		mResetTimer += clt::Timer::deltaTime;
	}
	else
	{
		mResetTimer = 0;
	}

	if (mResetTimer > 2 && mMode == mode::shoot)
	{
		mResetTimer;
		mMode = mode::movement;
		mSprite->mVisibility = true;
		mOwner->GetComponentOfType<clt::SpringArmComponent>()->SetRelativeLocation(Vector3::Zero);
		mBall->GetComponentOfType<clt::RigidBody>()->SetSimulate(false);
		mBall->SetActorLocation((mOwner->GetActorLocation() - mOwner->GetTransform().Forward()) - Vector3{ 0,0.5,0 });
	}
}

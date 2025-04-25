#include "BowlingController.h"

BowlingController::BowlingController() : PlayerController(), mMode(mode::movement), mRotation(-180)
{
	clt::Input::Get().MapKeysToAxis(EKey::A, EKey::D,"PlayerMovement");
	clt::Input::Get().MapKeyToAction(EKey::Space, "changeMod");
	//clt::Input::Get().MapKeyToAction(EKey::Space, "chargeShoot", EInputState::Held);
	//clt::Input::Get().MapKeyToAction(EKey::Space, "shoot", EInputState::Released);

	clt::Input::Get().RegisterAxisCallback("PlayerMovement", [this](float value) { this->Move(value); });
	clt::Input::Get().RegisterActionCallback("changeMod", [this] {this->ChangeMod(); });
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

}

void BowlingController::ChangeMod()
{
	auto* comp = mOwner->GetComponentOfType<clt::SpriteComponent>();
	switch (mMode)
	{
	case BowlingController::mode::movement:
		mMode = mode::rotation;
		comp->SetTexture("previewRotation");
		break;
	case BowlingController::mode::rotation:
		mMode = mode::shoot;
		break;
	case BowlingController::mode::shoot:
		mMode = mode::movement;
		comp->SetTexture("previewTrajectory");
		break;
	default:
		break;
	}
}

void BowlingController::Update()
{
}

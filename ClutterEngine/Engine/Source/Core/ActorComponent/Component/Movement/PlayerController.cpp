#include "pch.h"
#include <Core/ActorComponent/Components/Movements/PlayerController.h>
#include <Core/ActorComponent/Components/Graphics/FlipbookComponent.h>
#include <Input/Input.h>

using namespace clt;

PlayerController::PlayerController(std::string pMovementCallback, std::string pJumpCallback, float pSpeed) : Component(), mSpeed(pSpeed), mSprite(nullptr)
 {
	if(!Input::Get().RegisterVectCallback(pMovementCallback, [this](Vector2 value) { this->Movement(value); }));
	{
		Input::Get().RegisterAxisCallback(pMovementCallback, [this](float value) { this->Movement(value); });
	}
	if (!pJumpCallback.empty())
	{
		Input::Get().RegisterActionCallback(pJumpCallback, [this](void) { this->Jump(); });
	}
}

void PlayerController::OnCollisionEnter(const hitResult& result)
{

}

void PlayerController::OnCollisionStay(const hitResult& result)
{

}

void PlayerController::OnCollisionExit(const hitResult& result)
{

}

void PlayerController::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);
	mSprite = mOwner->GetComponentOfType<FlipbookComponent>();
	mRb = mOwner->GetComponentOfType<RigidBody2D>();
}

void PlayerController::Movement(Vector2 pDirection)
{
	mOwner->AddActorLocationOffset(pDirection * mSpeed);
	if(mSprite)
	{
		if (pDirection.x < 0)
		{
			mSprite->SetFlipX(true);
			mSprite->Play();
		}
		else if (pDirection.x > 0)
		{
			mSprite->SetFlipX(false);
			mSprite->Play();
		}
		else if (pDirection.y != 0)
		{
			mSprite->Play();
		}
		else
		{
			mSprite->Pause();
		}
	}
}

void PlayerController::Movement(float pDirection)
{
	mRb->AddVelocity({ pDirection, 0 });
	if (mSprite)
	{
		if (pDirection < 0)
		{
			mSprite->SetFlipX(true);
			mSprite->Play();
		}
		else if (pDirection > 0)
		{
			mSprite->SetFlipX(false);
			mSprite->Play();
		}
		else
		{
			mSprite->Pause();
		}
	}
}

void PlayerController::Jump()
{
	if (mRb->isGrounded)
	{
		mRb->AddVelocity({ 0, 200 });
	}
}

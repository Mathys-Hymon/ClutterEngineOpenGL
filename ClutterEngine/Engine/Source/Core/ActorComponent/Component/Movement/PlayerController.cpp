#include "pch.h"
#include <Core/ActorComponent/Components/Movements/PlayerController.h>
#include <Core/ActorComponent/Components/Graphics/Sprite/AnimatorComponent.h>
#include <Input/Input.h>

using namespace clt;

PlayerController::PlayerController(std::string pMovementCallback, std::string pJumpCallback, float pSpeed) : Component(), mMaxWalkSpeed(pSpeed), mSprite(nullptr), mAirControl(0.1f), mRb(nullptr), mIsJumping(false), mJumpHeight(230), mJumpAmount(1), mMaxSprintSpeed(pSpeed * 1.5f), mMovement(MovementMode::Walk), mIsCrouched(false), mIsSprinting(false)
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
	mSprite = mOwner->GetComponentOfType<AnimatorComponent>();
	mRb = mOwner->GetComponentOfType<RigidBody>();
}

void PlayerController::Movement(Vector2 pDirection)
{
	mOwner->AddActorLocationOffset(pDirection * mMaxWalkSpeed);
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
	if (mRb)
	{
		if (mRb->mIsGrounded)
		{
			mRb->AddVelocity({ pDirection * mMaxWalkSpeed, 0.0f , 0.0f});
		}
		else
		{
			mRb->AddVelocity({ pDirection * mMaxWalkSpeed * mAirControl, 0.0f , 0.0f});
			if (mIsJumping) mMovement = MovementMode::Jump;
			else mMovement = MovementMode::Falling;
		}
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
			else if (!mIsJumping)
			{
				mSprite->Pause();
			}
		}
	}
	
}

void PlayerController::Update()
{
	if (mRb && mRb->mIsGrounded)
	{
		if (mIsJumping && mRb->GetVelocity().y <= 1.0f)
		{
			mIsJumping = false;
			mOwner->GetComponentOfType<AnimatorComponent>()->PlayAnim("walk");
		}

		if (mIsSprinting) mMovement = MovementMode::Sprint;
		else if (mIsCrouched) mMovement = MovementMode::Crouch;
		else mMovement = MovementMode::Walk;
	}
}

void PlayerController::Jump()
{
	if (mRb && mRb->mIsGrounded)
	{
		mRb->AddVelocity({ 0, 230 });
		mOwner->GetComponentOfType<AnimatorComponent>()->PlayAnim("jump");
		mSprite->Play();
		mIsJumping = true;
	}
}

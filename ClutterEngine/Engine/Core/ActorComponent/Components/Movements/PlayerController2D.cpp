#include "pch.h"
#include <Core/ActorComponent/Components/Movements/PlayerController2D.h>
#include <Core/ActorComponent/Components/Graphics/Sprite/AnimatorComponent.h>
#include <Input/Inputs.h>

using namespace clt;

PlayerController2D::PlayerController2D(std::string pMovementCallback, std::string pJumpCallback, float pSpeed) : PlayerController(pSpeed)
 {
	if(!Inputs::Get().RegisterVectCallback(pMovementCallback, [this](Vector2 value) { this->Movement(value); }));
	{
		Inputs::Get().RegisterAxisCallback(pMovementCallback, [this](float value) { this->Movement(value); });
	}
	if (!pJumpCallback.empty())
	{
		Inputs::Get().RegisterActionCallback(pJumpCallback, [this](void) { this->Jump(); });
	}
}

void PlayerController2D::OnCollisionEnter(ColliderComponent* collider, const HitResult& result)
{

}

void PlayerController2D::OnCollisionStay(ColliderComponent* collider, const HitResult& result)
{

}

void PlayerController2D::OnCollisionExit(ColliderComponent* collider, const HitResult& result)
{

}

void PlayerController2D::SetOwner(Actor* pOwner)
{
	Component::SetOwner(pOwner);
	mSprite = mOwner->GetComponentOfType<AnimatorComponent>();
	mRb = mOwner->GetComponentOfType<RigidBody>();
}

void PlayerController2D::Movement(Vector2 pDirection)
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

void PlayerController2D::Movement(float pDirection)
{
	if (mRb)
	{
		if (mRb->IsGrounded())
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

void PlayerController2D::Update()
{
	if (mRb && mRb->IsGrounded())
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

void PlayerController2D::Jump()
{
	if (mRb && mRb->IsGrounded())
	{
		mRb->AddVelocity({ 0, 230 });
		mOwner->GetComponentOfType<AnimatorComponent>()->PlayAnim("jump");
		mSprite->Play();
		mIsJumping = true;
	}
}

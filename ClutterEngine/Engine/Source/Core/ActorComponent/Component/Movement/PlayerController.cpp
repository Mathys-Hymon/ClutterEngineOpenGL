#include "pch.h"
#include <Core/ActorComponent/Components/Movements/PlayerController.h>
#include <Core/ActorComponent/Components/Graphics/FlipbookComponent.h>
#include <Input/Input.h>

using namespace clt;

PlayerController::PlayerController(std::string pMovementCallback, std::string pJumpCallback, float pSpeed) : Component(), mSpeed(pSpeed), mSprite(nullptr)
{
	Input::Get().RegisterVectCallback(pMovementCallback, [this](Vector2 value) { this->Movement(value); });

	if (!pJumpCallback.empty())
	{
		Input::Get().RegisterActionCallback(pJumpCallback, [this](void) { this->Jump(); });
	}
}

void PlayerController::OnCollisionEnter(const hitResult& result)
{

}

void PlayerController::Start()
{
	mSprite = mOwner->GetComponentOfType<FlipbookComponent>();
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

void PlayerController::Jump()
{
	std::cout << "jump" << std::endl;
}

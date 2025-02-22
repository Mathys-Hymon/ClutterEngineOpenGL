#pragma once
#include <Core/ActorComponent/Component.h>
#include <Physics/Collision/ICollisionListener.h>

namespace clt
{
	class FlipbookComponent;
	class CLUTTER_API PlayerController : public Component , public ICollisionListener
	{
		float mSpeed;
		FlipbookComponent* mSprite;

	public:
		PlayerController(std::string pMovementCallback, std::string pJumpCallback = "", float pSpeed = 2);
		~PlayerController() = default;

		virtual void OnCollisionEnter(const hitResult& result) override;

		virtual void OnCollisionStay(const hitResult& result) override;

		virtual void OnCollisionExit(const hitResult& result) override;

		virtual void Start() override;

		virtual void Movement(Vector2 pDirection);

		virtual void Movement(float pDirection);

		virtual void Jump();
	};
}
#pragma once
#include <Core/ActorComponent/Components/Collisions/Collider2DComponent.h>

namespace clt
{
	class CLUTTER_API CircleCollider : public Collider2DComponent
	{
		float mRadius;

		bool CheckCircleVsCircle(CircleCollider* pOther, hitResult& outResult) const;

	public:
		 CircleCollider(float pRadius = 32);
		~CircleCollider() = default;

		float GetRadius() const { return mRadius; };

		bool CheckCollision(Collider2DComponent* pOther, hitResult& outResult) const override;
	};
}
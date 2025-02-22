#pragma once
#include <Core/ActorComponent/Component.h>
#include <Core/ActorComponent/Components/Collisions/HitResult.h>

namespace clt
{
	class Physics;
	class CLUTTER_API Collider2DComponent : public Component
	{
	public:
		enum class Type { AABB, Circle };

	protected:
		bool mTrigger = false;
		Type mType;

	public:
		virtual bool CheckCollision(Collider2DComponent* pOther, hitResult& outResult) const = 0;

		Type GetType() const { return mType; };
		bool IsTrigger() const { return mTrigger; };
	};
}
#pragma once
#include <Core/ActorComponent/Component.h>

namespace clt
{
	class Physics;
	class CLUTTER_API Collider2DComponent : public Component
	{
	protected:
		bool mTrigger = false;

	public:
		virtual bool CheckCollision(Collider2DComponent* pOther) = 0;
	};
}
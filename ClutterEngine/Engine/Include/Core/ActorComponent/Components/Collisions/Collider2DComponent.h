#pragma once
#include <Core/ActorComponent/Component.h>

namespace clt
{
	class Collider2DComponent : public Component
	{
		bool mTrigger = false;
		bool mStatic  = false;

		virtual float GetBoundingRadius() const = 0;
	};
}
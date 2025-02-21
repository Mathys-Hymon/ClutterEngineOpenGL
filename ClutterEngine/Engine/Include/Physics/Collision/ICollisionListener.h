#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/Collisions/HitResult.h>

namespace clt
{
	class CLUTTER_API ICollisionListener
	{
	public :
		virtual ~ICollisionListener() = default;
		virtual void OnNotify(hitResult result) = 0;
	};
}
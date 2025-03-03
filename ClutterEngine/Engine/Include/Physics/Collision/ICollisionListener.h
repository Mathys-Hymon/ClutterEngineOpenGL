#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/Collisions/HitResult.h>

namespace clt
{
	class CLUTTER_API ICollisionListener
	{
	public :
		virtual ~ICollisionListener() = default;
		virtual void OnCollisionEnter(const hitResult2D& result) = 0;
		virtual void OnCollisionStay (const hitResult2D& result) = 0;
		virtual void OnCollisionExit (const hitResult2D& result) = 0;
	};
}
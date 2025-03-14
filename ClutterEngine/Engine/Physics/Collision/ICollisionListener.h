#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/Collisions/HitResult.h>

namespace clt
{
	class CLUTTER_API ICollisionListener
	{
	public :
		virtual ~ICollisionListener() = default;
		virtual void OnCollisionEnter(const hitResult& result) = 0;
		virtual void OnCollisionStay (const hitResult& result) = 0;
		virtual void OnCollisionExit (const hitResult& result) = 0;

		virtual void OnTriggerEnter(const hitResult& result) = 0;
		virtual void OnTriggerStay (const hitResult& result) = 0;
		virtual void OnTriggerExit (const hitResult& result) = 0;
	};
}
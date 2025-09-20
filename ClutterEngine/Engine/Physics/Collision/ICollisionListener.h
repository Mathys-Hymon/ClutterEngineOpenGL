#pragma once
#include <Core/CCommon.h>
#include <Physics/HitResult.h>

namespace clt
{
	class CLUTTER_API ICollisionListener
	{
	public :
		virtual ~ICollisionListener() = default;
		virtual void OnCollisionEnter(ColliderComponent* collider, const HitResult& result) {};
		virtual void OnCollisionStay (ColliderComponent* collider, const HitResult& result) {};
		virtual void OnCollisionExit (ColliderComponent* collider, const HitResult& result) {};

		virtual void OnTriggerEnter(ColliderComponent* collider, const HitResult& result) {};
		virtual void OnTriggerStay (ColliderComponent* collider, const HitResult& result) {};
		virtual void OnTriggerExit (ColliderComponent* collider, const HitResult& result) {};
	};
}
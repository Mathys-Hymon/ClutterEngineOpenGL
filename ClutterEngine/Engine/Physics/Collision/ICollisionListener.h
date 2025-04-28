#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/Collisions/HitResult.h>

namespace clt
{
	class CLUTTER_API ICollisionListener
	{
	public :
		virtual ~ICollisionListener() = default;
		virtual void OnCollisionEnter(ColliderComponent* collider, const hitResult& result) {};
		virtual void OnCollisionStay (ColliderComponent* collider, const hitResult& result) {};
		virtual void OnCollisionExit (ColliderComponent* collider, const hitResult& result) {};

		virtual void OnTriggerEnter(ColliderComponent* collider, const hitResult& result) {};
		virtual void OnTriggerStay (ColliderComponent* collider, const hitResult& result) {};
		virtual void OnTriggerExit (ColliderComponent* collider, const hitResult& result) {};
	};
}
#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/Collisions/HitResult.h>

namespace clt
{
	class CLUTTER_API ICollisionListener
	{
	public :
		virtual ~ICollisionListener() = default;
		virtual void OnCollisionEnter(ColliderComponent* collider, const hitResult& result) = 0;
		virtual void OnCollisionStay (ColliderComponent* collider, const hitResult& result) = 0;
		virtual void OnCollisionExit (ColliderComponent* collider, const hitResult& result) = 0;

		virtual void OnTriggerEnter(ColliderComponent* collider, const hitResult& result) = 0;
		virtual void OnTriggerStay (ColliderComponent* collider, const hitResult& result) = 0;
		virtual void OnTriggerExit (ColliderComponent* collider, const hitResult& result) = 0;
	};
}
#pragma once
#include <Core/CCommon.h>
#include <Core/ActorComponent/Components/Physics/Collisions/ColliderComponent.h>
#include <Core/ActorComponent/Components/Physics/IRigidBody.h>
#include <Physics/Collision/CollisionEvent.h>

namespace clt
{
	class CLUTTER_API IPhysics
	{
	public:
		virtual ~IPhysics() = default;

		virtual void UpdatePhysics() = 0;

		virtual void AddRigidbody(IRigidbody* body) = 0;
		virtual void RemoveRigidBody(IRigidbody* body) = 0;

		virtual bool LineTrace(const Vector3& start, const Vector3& direction, float maxDistance, raycastHit& hit, bool debugPersistant = false, Actor* self = nullptr) = 0;
	};
}
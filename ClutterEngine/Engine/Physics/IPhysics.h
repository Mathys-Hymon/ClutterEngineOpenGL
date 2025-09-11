#pragma once
#include <Core/CCommon.h>

namespace clt
{
	class CLUTTER_API IPhysics
	{
	public:
		virtual ~IPhysics() = default;

		virtual void StepSimulation(float deltaTime) = 0;

		virtual class IRigidbody* CreateRigidbody() = 0;
		virtual void DestroyRigidBody(IRigidbody* body) = 0;

		virtual class ICollider* CreateCollider() = 0;
		virtual void DestroyCollider(ICollider* collider) = 0;
	};
}
#pragma once
#include <Core/ActorComponent/Component.h>

namespace clt
{
	class CLUTTER_API IRigidbody : public Component
	{
	public:
		virtual ~IRigidbody() = default;

		virtual void SetMass(float mass) = 0;
		virtual float GetMass() = 0;

		virtual void SetVelocity(const Vector3& vel) = 0;
		virtual Vector3 GetVelocity() = 0;

		virtual void ApplyForce(const Vector3& force) = 0;
		virtual void ApplyImpulse(const Vector3& impulse) = 0;

		virtual void AttachCollider(class ICollider* collider) = 0;
	};
}
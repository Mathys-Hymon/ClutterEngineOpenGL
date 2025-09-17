#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Vectors/Vector3.h>
#include <Core/ActorComponent/Component.h>

enum class CLUTTER_API ColliderShapeType
{
	Box,
	Sphere,
	Capsule,
	Mesh,
	Plane
};

namespace clt
{
	class CLUTTER_API ICollider : public Component
	{
	public:
		virtual ~ICollider() = default;

		virtual void SetShape(ColliderShapeType type, const Vector3& size) = 0;
		virtual ColliderShapeType GetShapeType() const = 0;

		virtual void SetIsTrigger(bool trigger) = 0;
		virtual bool IsTrigger() const = 0;

		virtual void SetFriction(float friction) = 0;
		virtual float GetFriction() const = 0;

		virtual void SetBounciness(float bounciness) = 0;
		virtual float GetBounciness() const = 0;

		virtual void Subscribe(class ICollisionListener* listener) = 0;
	};
}
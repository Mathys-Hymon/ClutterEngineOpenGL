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

NLOHMANN_JSON_SERIALIZE_ENUM(ColliderShapeType, {
		{ColliderShapeType::Box, "Box"},
		{ColliderShapeType::Sphere, "Sphere"},
		{ColliderShapeType::Capsule, "Capsule"},
		{ColliderShapeType::Plane, "Plane"},
		{ColliderShapeType::Mesh, "Mesh"}
	})

namespace clt
{
	class CLUTTER_API ICollider : public Component
	{
	public:

		ICollider(int drawOrder = 0) : Component(drawOrder) {};
		virtual ~ICollider() = default;

		virtual void SetShape(ColliderShapeType shape, Vector3 bounds) = 0;
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
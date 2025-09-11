#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Vectors/Vector3.h>

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
	class CLUTTER_API ICollider
	{
	public:
		virtual ~ICollider() = default;

		virtual void SetShape(ColliderShapeType type, const Vector3& size) = 0;
		virtual ColliderShapeType GetShapeType() const = 0;

		virtual void SetIsTrigger(bool trigger) = 0;
		virtual bool IsTrigger() = 0;
	};
}
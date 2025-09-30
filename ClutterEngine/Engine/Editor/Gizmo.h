#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Transforms/Transform.h>

namespace clt
{
	enum class GizmoMode
	{
		Translate,
		Rotate,
		Scale
	};

	class CLUTTER_API Gizmo
	{
		Transform mTransform;
		GizmoMode mMode;

	public:
		Gizmo() = default;
		~Gizmo() = default;

		void SetLocation(Vector3& loc) { mTransform.SetLocation(loc); };

		void SetRotation(Vector3& rot) { mTransform.SetRotation(rot); };
		void SetRotation(Quaternion& rot) { mTransform.SetRotation(rot); };

		void SetScale(Vector3& scale) { mTransform.SetScale(scale); };

		void Draw();

		void SetMode(GizmoMode mode) { mMode = mode; };

		Transform GetTransform() { return mTransform; };

	};
}
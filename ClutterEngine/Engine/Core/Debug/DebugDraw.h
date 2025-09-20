#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Quaternion.h>
#include <Graphics/Shader/ShaderProgram.h>
#include <Graphics/Shader/VertexArray.h>
#include <Core/Maths/Color.h>

namespace clt
{
	class CEngine;
	class RendererGL;
	class CLUTTER_API DebugDraw
	{
	protected:

		struct Line
		{
			Vector3 start;
			Vector3 end;
			Color color;
			float lineWidth = 1;
		};

		struct Box
		{
			Vector3 center;
			Vector3 extents;
			Color color;
			Quaternion rotation;
			float lineWidth = 1;
		};

		struct Sphere
		{
			Vector3 center;
			float radius;
			Color color;
			float lineWidth = 1;
		};

	public:

		DebugDraw() = default;
		~DebugDraw() = default;

		void Start();
		void Draw(const Matrix4Row& viewProj);
		void Close();

		void DrawLine(const Vector3& start, const Vector3& end, const Color& color = Color::Red, float lineThickness = 1, bool persistant = false);

		void DrawBox(const Vector3& center, const Vector3& extents, const Color& color = Color::Red, float lineThickness = 1, const Quaternion& rotation = Quaternion::Identity, bool persistant = false);

		void DrawSphere(const Vector3& center, float radius, const Color& color = Color::Red, float lineThickness = 1, bool persistant = false);

		void FlushPersistantDraw();
		void FlushPersistantLines();
		void FlushPersistantBoxes();
		void FlushPersistantSpheres();
	};
}
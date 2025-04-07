#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Quaternion.h>
#include <Graphics/Shader/ShaderProgram.h>
#include <Graphics/Shader/VertexArray.h>
#include <Core/Maths/Color.h>

namespace clt
{
	class RendererGL;
	class CLUTTER_API DebugDraw
	{
		DebugDraw() = default;

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

		std::vector<Line> mLines;   
		std::vector<Box> mBoxes;    
		std::vector<Sphere> mSpheres;

		ShaderProgram* mShader;
		VertexArray* mCubeVAO;
		VertexArray* mLineVAO;
		VertexArray* mSphereVAO;

		void Start();
		void Draw(Matrix4Row viewProj);
		void Close();

		friend RendererGL;

	public:

		DebugDraw(const DebugDraw&) = delete;
		DebugDraw& operator=(const DebugDraw&) = delete;

		static DebugDraw& Get();

		void DrawLine(const Vector3& start, const Vector3& end, const Color& color = Color::red, float lineThickness = 1);

		void DrawBox(const Vector3& center, const Vector3& extents, const Color& color = Color::red, float lineThickness = 1, const Quaternion & rotation = Quaternion::Identity);

		void DrawSphere(const Vector3& center, float radius, const Color& color = Color::red, float lineThickness = 1);
	};
}
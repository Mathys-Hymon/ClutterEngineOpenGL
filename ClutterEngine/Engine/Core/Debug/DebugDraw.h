#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Quaternion.h>
#include <Graphics/Shader/ShaderProgram.h>
#include <Graphics/Shader/VertexArray.h>
#include <Core/Maths/Color.h>

namespace clt
{
	/**
  * @brief Forward declaration of the engine class.
  */
	class CEngine;

	/**
  * @brief Forward declaration of the OpenGL renderer class.
  */
	class RendererGL;

	/**
  * @brief Provides debug drawing utilities for lines, boxes, and spheres.
  * 
  * This class allows drawing of debug primitives in the scene for visualization purposes.
  * It supports both transient and persistent debug objects.
  */
	class CLUTTER_API DebugDraw
	{
		/**
   * @brief Default constructor. Private to enforce singleton pattern.
   */
		DebugDraw() = default;

		/**
   * @brief Pointer to the engine instance.
   */
		CEngine* mEngine;

		/**
   * @brief Represents a debug line.
   */
		struct Line
		{
			Vector3 start;      ///< Start position of the line.
			Vector3 end;        ///< End position of the line.
			Color color;        ///< Color of the line.
			float lineWidth = 1;///< Thickness of the line.
		};

		/**
   * @brief Represents a debug box.
   */
		struct Box
		{
			Vector3 center;         ///< Center position of the box.
			Vector3 extents;        ///< Half-extents of the box.
			Color color;            ///< Color of the box.
			Quaternion rotation;    ///< Rotation of the box.
			float lineWidth = 1;    ///< Thickness of the box lines.
		};

		/**
   * @brief Represents a debug sphere.
   */
		struct Sphere
		{
			Vector3 center;     ///< Center position of the sphere.
			float radius;       ///< Radius of the sphere.
			Color color;        ///< Color of the sphere.
			float lineWidth = 1;///< Thickness of the sphere lines.
		};

		std::vector<Line> mLines;                ///< List of transient lines.
		std::vector<Line> mPersistantLines;      ///< List of persistent lines.

		std::vector<Box> mBoxes;                 ///< List of transient boxes.
		std::vector<Box> mPersistantBoxes;       ///< List of persistent boxes.

		std::vector<Sphere> mSpheres;            ///< List of transient spheres.
		std::vector<Sphere> mPersistantSpheres;  ///< List of persistent spheres.

		ShaderProgram* mShader;      ///< Shader used for debug drawing.
		VertexArray* mCubeVAO;       ///< Vertex array object for box drawing.
		VertexArray* mSphereVAO;     ///< Vertex array object for sphere drawing.

		GLuint mLineVAO;             ///< OpenGL VAO for lines.
		GLuint mLineVBO;             ///< OpenGL VBO for lines.

		/**
   * @brief Initializes the debug draw system.
   * @param pEngine Pointer to the engine instance.
   */
		void Start(CEngine* pEngine);

		/**
   * @brief Renders all debug primitives.
   * @param viewProj The view-projection matrix.
   */
		void Draw(Matrix4Row viewProj);

		/**
   * @brief Cleans up debug draw resources.
   */
		void Close();

		friend RendererGL;

	public:

		/**
   * @brief Deleted copy constructor.
   */
		DebugDraw(const DebugDraw&) = delete;

		/**
   * @brief Deleted copy assignment operator.
   */
		DebugDraw& operator=(const DebugDraw&) = delete;

		/**
   * @brief Gets the singleton instance of DebugDraw.
   * @return Reference to the DebugDraw instance.
   */
		static DebugDraw& Get();

		/**
   * @brief Draws a line in the scene.
   * @param start Start position of the line.
   * @param end End position of the line.
   * @param color Color of the line.
   * @param lineThickness Thickness of the line.
   * @param persistant If true, the line persists until flushed.
   */
		void DrawLine(const Vector3& start, const Vector3& end, const Color& color = Color::Red, float lineThickness = 1, bool persistant = false);

		/**
   * @brief Draws a box in the scene.
   * @param center Center position of the box.
   * @param extents Half-extents of the box.
   * @param color Color of the box.
   * @param lineThickness Thickness of the box lines.
   * @param rotation Rotation of the box.
   * @param persistant If true, the box persists until flushed.
   */
		void DrawBox(const Vector3& center, const Vector3& extents, const Color& color = Color::Red, float lineThickness = 1, const Quaternion & rotation = Quaternion::Identity, bool persistant = false);

		/**
   * @brief Draws a sphere in the scene.
   * @param center Center position of the sphere.
   * @param radius Radius of the sphere.
   * @param color Color of the sphere.
   * @param lineThickness Thickness of the sphere lines.
   * @param persistant If true, the sphere persists until flushed.
   */
		void DrawSphere(const Vector3& center, float radius, const Color& color = Color::Red, float lineThickness = 1, bool persistant = false);

		/**
   * @brief Flushes all persistent debug primitives.
   */
		void FlushPersistantDraw();

		/**
   * @brief Flushes all persistent lines.
   */
		void FlushPersistantLines();

		/**
   * @brief Flushes all persistent boxes.
   */
		void FlushPersistantBoxes();

		/**
   * @brief Flushes all persistent spheres.
   */
		void FlushPersistantSpheres();
	};
}
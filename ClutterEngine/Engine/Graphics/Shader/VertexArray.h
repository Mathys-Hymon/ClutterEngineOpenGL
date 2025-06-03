#pragma once
#include <Core/CCommon.h>
#include <glad/glad.h>

namespace clt
{
	/**
  * @brief Specifies the usage pattern of the buffer.
  */
	enum class BufferUsage
	{
		STATIC = GL_STATIC_DRAW,  /**< Data will rarely change. */
		DYNAMIC = GL_DYNAMIC_DRAW,/**< Data will change frequently. */
		STREAM = GL_STREAM_DRAW   /**< Data will change every frame. */
	};

	/**
  * @brief Represents an OpenGL Vertex Array and its associated Vertex Buffer.
  */
	class CLUTTER_API VertexArray
	{
		u32 mVerticeCount;      /**< Number of vertices in the buffer. */

		u32 mVertexArrayId;     /**< OpenGL Vertex Array Object ID. */
		u32 mVertexBufferId;    /**< OpenGL Vertex Buffer Object ID. */

		BufferUsage mUsage;     /**< Usage pattern for the buffer. */

	public:
		/**
   * @brief Constructs an empty VertexArray with the specified usage.
   * @param usage The buffer usage pattern.
   */
		VertexArray(BufferUsage usage = BufferUsage::STATIC) : mVerticeCount(0), mVertexArrayId(0), mVertexBufferId(0), mUsage(usage) {};

		/**
   * @brief Constructs a VertexArray and initializes it with vertex data.
   * @param pVertices Pointer to the vertex data.
   * @param pVerticeCount Number of vertices.
   * @param usage The buffer usage pattern.
   */
		VertexArray(const float* pVertices, u32 pVerticeCount, BufferUsage usage = BufferUsage::STATIC);

		/**
   * @brief Destructor. Releases OpenGL resources.
   */
		~VertexArray();

		/**
   * @brief Sets the vertex data for the array.
   * @param pVertices Pointer to the vertex data.
   * @param pVerticeCount Number of vertices.
   */
		void Set(const float* pVertices, u32 pVerticeCount);

		/**
   * @brief Binds the vertex array for rendering.
   */
		void Bind();

		/**
   * @brief Unbinds the vertex array.
   */
		void Unbind();

		/**
   * @brief Gets the number of vertices in the array.
   * @return The number of vertices.
   */
		u32 GetVerticeCount() const { return mVerticeCount; };
	};
}

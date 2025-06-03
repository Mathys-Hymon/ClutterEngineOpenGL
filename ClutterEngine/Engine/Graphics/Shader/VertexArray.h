#pragma once
#include <Core/CCommon.h>
#include <glad/glad.h>

namespace clt
{
	enum class BufferUsage
	{
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW,
		STREAM = GL_STREAM_DRAW
	};

	class CLUTTER_API VertexArray
	{
		u32 mVerticeCount;

		u32 mVertexArrayId;
		u32 mVertexBufferId;

		BufferUsage mUsage;

	public:
		VertexArray(BufferUsage usage = BufferUsage::STATIC) : mVerticeCount(0), mVertexArrayId(0), mVertexBufferId(0), mUsage(usage) {};
		VertexArray(const float* pVertices, u32 pVerticeCount, BufferUsage usage = BufferUsage::STATIC);
		~VertexArray();

		void Set(const float* pVertices, u32 pVerticeCount);

		void Bind();
		void Unbind();

		u32 GetVerticeCount() const { return mVerticeCount; };
	};
}
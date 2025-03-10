#pragma once
#include <Core/CCommon.h>

namespace clt
{
	class CLUTTER_API VertexArray
	{
		u32 mVerticeCount;

		u32 mVertexArrayId;
		u32 mVertexBufferId;

	public:
		VertexArray() : mVerticeCount(0), mVertexArrayId(0), mVertexBufferId(0) {};
		VertexArray(const float* pVertices, u32 pVerticeCount);
		~VertexArray();

		void Set(const float* pVertices, u32 pVerticeCount);

		void Bind();
		void Unbind();

		u32 GetVerticeCount() const { return mVerticeCount; };
	};
}
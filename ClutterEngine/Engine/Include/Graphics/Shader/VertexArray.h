#pragma once
#include <Core/CCommon.h>

namespace clt
{
	class CLUTTER_API VertexArray
	{
		u32 mVerticeCount;
		u32 mIndexCount;

		u32 mVertexArrayId;
		u32 mVertexBufferId;
		u32 mIndexBufferId;

	public:
		VertexArray() : mVerticeCount(0), mIndexCount(0), mVertexArrayId(0), mVertexBufferId(0), mIndexBufferId(0) {};
		VertexArray(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount);
		~VertexArray();

		void Set(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount);

		void Bind();
		void Unbind();

		u32 GetVerticeCount() const { return mVerticeCount; };
		u32 GetIndicesCount() const { return mIndexCount; };
	};
}
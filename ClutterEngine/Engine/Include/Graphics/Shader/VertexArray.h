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
		VertexArray(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount);
		~VertexArray();

		void Bind();
		void Unbind();

		u32 GetVerticeCount() const { return mVerticeCount; };
		u32 GetIndicesCount() const { return mIndexCount; };
	};
}
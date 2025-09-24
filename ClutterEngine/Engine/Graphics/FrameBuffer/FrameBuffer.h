#pragma once
#include <Core/CCommon.h>
#include <glad/glad.h>

namespace clt
{
	struct CLUTTER_API FrameBufferSpecification
	{
		u32 Width = 1280;
		u32 Height = 720;
		bool HasDepth = true;
		bool HasColor = true;
		u32 ColorAttachments = 1;
	};

	class CLUTTER_API FrameBuffer
	{
		GLuint mRendererID = 0;
		FrameBufferSpecification mSpec;

		std::vector<GLuint> mColorAttachments;
		GLuint mDepthAttachment = 0;

		void Invalidate();

	public :
		FrameBuffer(const FrameBufferSpecification& spec);
		~FrameBuffer();

		void Bind();
		void Unbind();
		void Resize(u32 width, u32 height);

		u32 GetWidth() const { return mSpec.Width; }
		u32 GetHeight() const { return mSpec.Height; }

		GLuint GetColorAttachment(u32 index = 0) const { return mColorAttachments[index]; };
		const FrameBufferSpecification& GetSpecification() const { return mSpec; };
	};
}
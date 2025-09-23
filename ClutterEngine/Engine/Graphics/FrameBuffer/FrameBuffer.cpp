#include <pch.h>
#include <Graphics/FrameBuffer/FrameBuffer.h>

using namespace clt;


FrameBuffer::FrameBuffer(const FrameBufferSpecification& spec) : mSpec(spec)
{
	Invalidate();
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &mRendererID);
    glDeleteTextures((GLsizei)mColorAttachments.size(), mColorAttachments.data());

    if (mDepthAttachment) glDeleteRenderbuffers(1, &mDepthAttachment);
}

void FrameBuffer::Invalidate()
{
    if (mRendererID)
    {
        glDeleteFramebuffers(1, &mRendererID);
        glDeleteTextures((GLsizei)mColorAttachments.size(), mColorAttachments.data());
        if (mDepthAttachment)
            glDeleteRenderbuffers(1, &mDepthAttachment);

        mColorAttachments.clear();
        mDepthAttachment = 0;
    }

    glGenFramebuffers(1, &mRendererID);
    glBindFramebuffer(GL_FRAMEBUFFER, mRendererID);

    mColorAttachments.reserve(mSpec.ColorAttachments);
    glGenTextures(mSpec.ColorAttachments, mColorAttachments.data());

    for (u32 i = 0; i < mSpec.ColorAttachments; i++)
    {
        glBindTexture(GL_TEXTURE_2D, mColorAttachments[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mSpec.Width, mSpec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, mColorAttachments[i], 0);
    }

    if (mSpec.HasDepth)
    {
        glGenRenderbuffers(1, &mDepthAttachment);
        glBindRenderbuffer(GL_RENDERBUFFER, mDepthAttachment);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mSpec.Width, mSpec.Height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthAttachment);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) CLUTTER_ERROR("Framebuffer incomplet");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mRendererID);
    glViewport(0, 0, mSpec.Width, mSpec.Height);
}

void FrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Resize(u32 width, u32 height)
{
    if (width == 0 || height == 0)
        return;

    mSpec.Width = width;
    mSpec.Height = height;
    Invalidate();
}
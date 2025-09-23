#include "pch.h"
#include <Graphics/Shader/VertexArray.h>
#include "FrameBuffer.h"

using namespace clt;

VertexArray::VertexArray(const float* pVertices, u32 pVerticeCount, BufferUsage usage)
	: mVerticeCount(pVerticeCount), mVertexArrayId(0), mVertexBufferId(0), mUsage(usage)
{
	Set(pVertices, pVerticeCount);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBufferId);
	glDeleteVertexArrays(1, &mVertexArrayId);
}

void VertexArray::Set(const float* pVertices, u32 pVerticeCount)
{
    mVerticeCount = pVerticeCount;

    if (mVertexArrayId == 0) // VAO
    {
        glGenVertexArrays(1, &mVertexArrayId);
        glBindVertexArray(mVertexArrayId);
        glGenBuffers(1, &mVertexBufferId);
    }

    glBindVertexArray(mVertexArrayId);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);

    if (mUsage == BufferUsage::STATIC)
    {
        glBufferData(GL_ARRAY_BUFFER, pVerticeCount * sizeof(float) * 8, pVertices, GL_STATIC_DRAW);
    }
    else // DYNAMIC or STREAM
    {
        glBufferData(GL_ARRAY_BUFFER, pVerticeCount * sizeof(float) * 8, nullptr, (GLenum)mUsage);
        glBufferSubData(GL_ARRAY_BUFFER, 0, pVerticeCount * sizeof(float) * 8, pVertices);
    }

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));

    glBindVertexArray(0);
}

void VertexArray::Bind()
{
	glBindVertexArray(mVertexArrayId);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

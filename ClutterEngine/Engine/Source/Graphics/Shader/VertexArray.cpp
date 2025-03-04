#include "pch.h"
#include <Graphics/Shader/VertexArray.h>
#include <glad/glad.h>

using namespace clt;

VertexArray::VertexArray(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount) 
	: mVerticeCount(pVerticeCount), mIndexCount(pIndexCount), mVertexArrayId(0), mVertexBufferId(0), mIndexBufferId(0)
{
	Set(pVertices, pVerticeCount, pIndices, pIndexCount);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBufferId);
	glDeleteBuffers(1, &mIndexBufferId);
	glDeleteVertexArrays(1, &mVertexArrayId);
}

void VertexArray::Set(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount)
{
    if (mVertexArrayId == 0)
    {
        glGenVertexArrays(1, &mVertexArrayId);
        glGenBuffers(1, &mVertexBufferId);
        glGenBuffers(1, &mIndexBufferId);
    }

    glBindVertexArray(mVertexArrayId);

    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, pVerticeCount * 5 * sizeof(float), pVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pIndexCount * sizeof(u32), pIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

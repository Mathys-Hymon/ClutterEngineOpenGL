#include "pch.h"
#include <Graphics/Shader/VertexArray.h>
#include <glad/glad.h>

using namespace clt;

VertexArray::VertexArray(const float* pVertices, u32 pVerticeCount) 
	: mVerticeCount(pVerticeCount), mVertexArrayId(0), mVertexBufferId(0)
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
    if (mVertexArrayId == 0) // VAO
    {
        glGenVertexArrays(1, &mVertexArrayId);
        glBindVertexArray(mVertexArrayId);
    }

    // VBO
    glGenBuffers(1, &mVertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, mVerticeCount * 8 * sizeof(float), pVertices, GL_STATIC_DRAW);

    //Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    //Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    //Texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));


}


void VertexArray::Bind()
{
	glBindVertexArray(mVertexArrayId);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

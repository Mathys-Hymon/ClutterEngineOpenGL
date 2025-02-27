#include "pch.h"
#include <Graphics/Shader/VertexArray.h>
#include <glad/glad.h>

using namespace clt;

VertexArray::VertexArray(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount) 
	: mVerticeCount(pVerticeCount), mIndexCount(pIndexCount), mVertexArrayId(0), mVertexBufferId(0), mIndexBufferId(0)
{
	// Generate VAO
	glGenVertexArrays(1, &mVertexArrayId);
	glBindVertexArray(mVertexArrayId);

	// Generate VBO
	glGenBuffers(1, &mVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, mVerticeCount * 4 * sizeof(float), pVertices, GL_STATIC_DRAW);

	// Generate Index Buffer
	glGenBuffers(1, &mIndexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndexCount * sizeof(u32), pIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBufferId);
	glDeleteBuffers(1, &mIndexBufferId);
	glDeleteVertexArrays(1, &mVertexArrayId);
}

void VertexArray::Bind()
{
	glBindVertexArray(mVertexArrayId);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

#include "pch.h"
#include <Core/Debug/DebugDraw.h>

using namespace clt;

const auto basicVertPah = "Content/Shaders/basic.vert";
const auto basicFragPath = "Content/Shaders/basic.frag";

DebugDraw& DebugDraw::Get()
{
    static DebugDraw instance;
    return instance;
}

void DebugDraw::Start()
{
    mShader = new Shader();
    mShader->Load(basicVertPah, basicFragPath);

    mVAO = new VertexArray();
}

void DebugDraw::Draw(Matrix4Row viewProj)
{
    mShader->Use();
    mShader->SetMat4Row("uViewProj", viewProj);
    mVAO->Bind();

    for (const auto& line : mLines)
    {
        Vector3 vertices[2] = { line.start, line.end };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        mShader->SetVec4f("uColor", line.color);

        glDrawArrays(GL_LINES, 0, 2);
    }

    for (const auto& box : mBoxes)
    {
        Matrix4Row transform = Matrix4Row::CreateTranslation(box.center) * Matrix4Row::CreateFromQuaternion(box.rotation);
        Vector3 vertices[8];
        for (int i = 0; i < 8; i++)
        {
            Vector3 localPos = {
                (i & 1) ? box.extents.x : -box.extents.x,
                (i & 2) ? box.extents.y : -box.extents.y,
                (i & 4) ? box.extents.z : -box.extents.z
            };
            vertices[i] = transform.CreateScale(localPos);
        }

        const int edges[24] = {
            0, 1, 1, 3, 3, 2, 2, 0, // Face avant
            4, 5, 5, 7, 7, 6, 6, 4, // Face arrière
            0, 4, 1, 5, 2, 6, 3, 7  // Arêtes latérales
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        mShader->SetVec4f("uColor", box.color);

        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, edges);
    }

    mLines.clear();
    mBoxes.clear();
    mSpheres.clear();
}

void DebugDraw::Close()
{
    delete mShader;
    mShader = nullptr;
}

void DebugDraw::DrawLine(const Vector3& start, const Vector3& end, const Color& color)
{
    mLines.push_back({ start, end, color });
}

void DebugDraw::DrawBox(const Vector3& center, const Vector3& extents, const Color& color, const Quaternion& rotation)
{
    mBoxes.push_back({ center, extents, color, rotation });
}

void DebugDraw::DrawSphere(const Vector3& center, float radius, const Color& color)
{
    mSpheres.push_back({ center,radius,color });
}

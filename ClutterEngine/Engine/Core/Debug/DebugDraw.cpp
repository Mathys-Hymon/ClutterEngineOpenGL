#include "pch.h"
#include <Core/Debug/DebugDraw.h>
#include <Core/Maths/Transforms/Transform.h>
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/CEngine.h>
#include <glad/glad.h>

using namespace clt;

// --- Shaders for Debug Drawing: Vertex Shader and Fragment Shader ---
const char* debugVertexShader = R"(
#version 460 core
layout (location = 0) in vec3 aPos;          // Vertex position

uniform mat4 uViewProj;                      // Combined view and projection matrix
uniform mat4 uModel;                         // Model transformation matrix
void main() {
    gl_Position = vec4(aPos, 1.0) * uModel * uViewProj;  // Transform vertex position
}
)";

const char* debugFragmentShader = R"(
#version 460 core
out vec4 FragColor;        // Output color
uniform vec4 uColor;       // Uniform color for the debug shapes
void main() {
    FragColor = uColor;    // Set fragment color
}
)";

// --- Constructor ---
DebugDraw::DebugDraw(CEngine& engine)
    : mShader(nullptr), mCubeVAO(nullptr), mSphereVAO(nullptr), mLineVAO(0), mLineVBO(0), mEngine(engine)
{
    if (!mEngine.IsEditorMode())
        return;

    // Shader
    mShader = new ShaderProgram();
    Shader* vert = new Shader();
    Shader* frag = new Shader();
    vert->Load(debugVertexShader, ShaderType::VERTEX, false);
    frag->Load(debugFragmentShader, ShaderType::FRAGMENT, false);
    mShader->Compose({ frag, vert });

    // Line VAO/VBO
    float lineVertices[6] = { 0,0,0, 1,0,0 };
    glGenVertexArrays(1, &mLineVAO);
    glGenBuffers(1, &mLineVBO);
    glBindVertexArray(mLineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mLineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    // Cube VAO (unit cube wireframe)
    constexpr float cubeWireframe[] = {
        // Edge 1: v0 -> v1 (front top edge)
    -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
     // Edge 2: v1 -> v2 (front right edge)
  0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
  0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
  // Edge 3: v2 -> v3 (front bottom edge)
0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
// Edge 4: v3 -> v0 (front left edge)
-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,

// Edge 5: v4 -> v5 (back top edge)
-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
 // Edge 6: v5 -> v6 (back right edge)
0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
// Edge 7: v6 -> v7 (back bottom edge)
0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
// Edge 8: v7 -> v4 (back left edge)
-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,

// Edge 9: v0 -> v4 (connecting top left edge)
-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  0.0f,   0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,   0.0f,  0.0f,  0.0f,   0.0f, 0.0f,
// Edge 10: v1 -> v5 (connecting top right edge)
0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  0.0f,   1.0f, 0.0f,
0.5f,  0.5f, -0.5f,   0.0f,  0.0f,  0.0f,   1.0f, 0.0f,
// Edge 11: v2 -> v6 (connecting bottom right edge)
0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  0.0f,   1.0f, 1.0f,
0.5f, -0.5f, -0.5f,   0.0f,  0.0f,  0.0f,   1.0f, 1.0f,
// Edge 12: v3 -> v7 (connecting bottom left edge)
-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  0.0f,   0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,   0.0f,  0.0f,  0.0f,   0.0f, 1.0f
    };

    mCubeVAO = new VertexArray(cubeWireframe, sizeof(cubeWireframe) / (sizeof(float) * 8));

    // Sphere VAO (dynamic)
    mSphereVAO = new VertexArray(nullptr, 0, BufferUsage::DYNAMIC);
}

// --- Start / Init ---
void DebugDraw::Start()
{

}

// --- Draw ---
void DebugDraw::Draw(const Matrix4Row& viewProj)
{
    if (!mEngine.IsEditorMode()) return;

    mShader->Use();
    mShader->SetMat4Row("uViewProj", viewProj);

    // --- Lines ---
    glBindVertexArray(mLineVAO);
    for (auto& line : mLines)
    {
        Matrix4Row model = Matrix4Row::CreateTranslation(Vector3::Zero);
        mShader->SetMat4Row("uModel", model);

        float vertices[] = {
            line.start.x, line.start.y, line.start.z,
            line.end.x,   line.end.y,   line.end.z
        };
        glBindBuffer(GL_ARRAY_BUFFER, mLineVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        mShader->SetVec4f("uColor", line.color);
        glLineWidth(line.lineWidth);
        glDrawArrays(GL_LINES, 0, 2);
    }
    mLines.clear();

    for (auto& line : mPersistentLines)
    {
        Matrix4Row model = Matrix4Row::CreateTranslation(Vector3::Zero);
        mShader->SetMat4Row("uModel", model);

        float vertices[] = {
            line.start.x, line.start.y, line.start.z,
            line.end.x,   line.end.y,   line.end.z
        };
        glBindBuffer(GL_ARRAY_BUFFER, mLineVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        mShader->SetVec4f("uColor", line.color);
        glLineWidth(line.lineWidth);
        glDrawArrays(GL_LINES, 0, 2);
    }
    glBindVertexArray(0);

    // --- Boxes ---
    mCubeVAO->Bind();

    for (const auto& box : mBoxes)
    {
        Matrix4Row tempTransform = Transform{ box.center, box.extents * 2, box.rotation }.GetMat4Transform();
        // Set the transformation matrix for the cube
        mShader->SetMat4Row("uModel", tempTransform);

        // Set the cube's color
        mShader->SetVec4f("uColor", box.color);

        glLineWidth(box.lineWidth);
        glDrawArrays(GL_LINES, 0, mCubeVAO->GetVerticeCount());
    }
    mBoxes.clear();

    for (const auto& box : mPersistentBoxes)
    {
        Matrix4Row tempTransform = Transform{ box.center, box.extents * 2, box.rotation }.GetMat4Transform();
        // Set the transformation matrix for the cube
        mShader->SetMat4Row("uModel", tempTransform);

        // Set the cube's color
        mShader->SetVec4f("uColor", box.color);

        glLineWidth(box.lineWidth);
        glDrawArrays(GL_LINES, 0, mCubeVAO->GetVerticeCount());
    }
    mCubeVAO->Unbind();

    // --- Spheres ---
    mSphereVAO->Bind();
    for (auto& sphere : mSpheres)
    {
        int segments = 16;
        std::vector<float> sphereVertices((segments + 1) * 3);

        for (int i = 0; i <= segments; i++)
        {
            float theta = (float)i / (float)segments * 2.0f * 3.14159265f;
            float x = cosf(theta) * sphere.radius;
            float z = sinf(theta) * sphere.radius;
            sphereVertices[i * 3 + 0] = x + sphere.center.x;
            sphereVertices[i * 3 + 1] = sphere.center.y;
            sphereVertices[i * 3 + 2] = z + sphere.center.z;
        }

        mSphereVAO->Set(sphereVertices.data(), segments + 1);
        mShader->SetMat4Row("uModel", Matrix4Row::Identity);
        mShader->SetVec4f("uColor", sphere.color);

        glLineWidth(sphere.lineWidth);
        glDrawArrays(GL_LINE_LOOP, 0, segments + 1);
    }
    mSpheres.clear();
    mSphereVAO->Unbind();
}

// --- Close ---
void DebugDraw::Close()
{
    delete mShader;
    mShader = nullptr;

    glDeleteVertexArrays(1, &mLineVAO);
    glDeleteBuffers(1, &mLineVBO);

    delete mCubeVAO;
    mCubeVAO = nullptr;

    delete mSphereVAO;
    mSphereVAO = nullptr;

    FlushPersistantDraw();
}

// --- Draw primitives ---
void DebugDraw::DrawLine(const Vector3& start, const Vector3& end, const Color& color, float lineThickness, bool persistant)
{
    if (persistant) mPersistentLines.push_back({ start,end,color,lineThickness });
    else mLines.push_back({ start,end,color,lineThickness });
}

void DebugDraw::DrawBox(const Vector3& center, const Vector3& extents, const Color& color, float lineThickness, const Quaternion& rotation, bool persistant)
{
    if (persistant) mPersistentBoxes.push_back({ center,extents,color,rotation,lineThickness });
    else mBoxes.push_back({ center,extents,color,rotation,lineThickness });
}

void DebugDraw::DrawSphere(const Vector3& center, float radius, const Color& color, float lineThickness, bool persistant)
{
    if (persistant) mPersistentSpheres.push_back({ center,radius,color,lineThickness });
    else mSpheres.push_back({ center,radius,color,lineThickness });
}

// --- Flush persistent ---
void DebugDraw::FlushPersistantDraw()
{
    FlushPersistantBoxes();
    FlushPersistantLines();
    FlushPersistantSpheres();
}

void DebugDraw::FlushPersistantLines()
{
    mPersistentLines.clear();
}

void DebugDraw::FlushPersistantBoxes()
{
    mPersistentBoxes.clear();
}

void DebugDraw::FlushPersistantSpheres()
{
    mPersistentSpheres.clear();
}

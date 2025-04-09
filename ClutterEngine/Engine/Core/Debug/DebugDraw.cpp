#include "pch.h"
#include <Core/Debug/DebugDraw.h>
#include <Core/Maths/Transforms/Transform.h>
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

// --- DebugDraw Class Implementation ---
DebugDraw& DebugDraw::Get()
{
    static DebugDraw instance;  // Singleton instance for DebugDraw
    return instance;
}

// Start the debug drawing, this initializes the necessary shaders and buffers
void DebugDraw::Start(CEngine* pEngine)
{
    mEngine = pEngine;

    if (mEngine->isEditorMode())
    {

        // Create and load the shader program from the provided source code
        mShader = new ShaderProgram();
        Shader* frag = new Shader();
        frag->Load(debugFragmentShader, ShaderType::FRAGMENT, false);
        Shader* vert = new Shader();
        vert->Load(debugVertexShader, ShaderType::VERTEX, false);
        mShader->Compose({ frag, vert });


        // Initialize the Vertex Array Object (VAO) for drawing lines (2 vertices)
        mLineVAO = new VertexArray(nullptr, 2, BufferUsage::DYNAMIC);

        // Cube edges defined by 24 vertices (pairs of vertices for each edge)
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


        // Initialize the VAO for cubes (8 vertices, 24 edges for a wireframe)
        mCubeVAO = new VertexArray(cubeWireframe, sizeof(cubeWireframe) / (sizeof(float) * 8));

        mSphereVAO = new VertexArray(nullptr, 0, BufferUsage::DYNAMIC);
    }
}

// Draw the debug objects (lines, boxes, spheres)
void DebugDraw::Draw(Matrix4Row viewProj)
{
    if (mEngine->isEditorMode())
    {
        // Use the shader program for drawing
        mShader->Use();
        mShader->SetMat4Row("uViewProj", viewProj);  // Set the combined view and projection matrix

        mLineVAO->Bind();
        // Draw lines (e.g., for drawing lines between points)
        for (const auto& line : mLines)
        {
            // Set up vertices for the line (2 points)
            Vector3 vertices[2] = { line.start, line.end };

            // Update the line's vertices in the VAO (dynamic update for each frame)
            mLineVAO->Set(reinterpret_cast<float*>(vertices), 2);

            // Set the line's color
            mShader->SetVec4f("uColor", line.color);

            glLineWidth(line.lineWidth);
            glDrawArrays(GL_LINES, 0, 2);
        }

        mCubeVAO->Bind();

        // Draw boxes (wireframe cubes)
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

        mCubeVAO->Unbind();
        mSphereVAO->Bind();

        for (const auto& sphere : mSpheres)
        {
            int segments = 16;              // Number of segments for the circle
            int vertexCount = segments + 1; // We generate an extra vertex to close the loop

            // Create a float array to store vertex data (position, normal, texCoord) for each vertex
            // Each vertex has 8 floats: 3 for position, 3 for normal, 2 for texture coordinates
            std::vector<float> sphereData;
            sphereData.resize(vertexCount * 8);

            // Generate vertices for a circle in the XZ plane at the origin with given sphere.radius
            for (int i = 0; i < vertexCount; i++)
            {
                float theta = (float)i / segments * 2.0f * 3.14159265f;
                float x = cosf(theta) * sphere.radius;
                float z = sinf(theta) * sphere.radius;

                // Set position (x, 0, z)
                sphereData[i * 8 + 0] = x;
                sphereData[i * 8 + 1] = 0.0f;
                sphereData[i * 8 + 2] = z;

                // Set a dummy normal
                sphereData[i * 8 + 3] = 0.0f;
                sphereData[i * 8 + 4] = 1.0f;
                sphereData[i * 8 + 5] = 0.0f;

                // Set dummy texture coordinates
                sphereData[i * 8 + 6] = 0.0f;
                sphereData[i * 8 + 7] = 0.0f;
            }

            // Create a model transform that translates the circle to the sphere's center.
            // Since our circle is generated at the origin, we only need translation.
            Matrix4Row model = Matrix4Row::CreateTranslation(sphere.center);
            mShader->SetMat4Row("uModel", model);
            mShader->SetVec4f("uColor", sphere.color);

            // Update the sphere VAO with the generated vertex data.
            // 'vertexCount' is the number of vertices (each vertex has 8 floats).
            mSphereVAO->Set(sphereData.data(), vertexCount);

            // Set the line width for drawing the sphere outline
            glLineWidth(sphere.lineWidth);

            // Draw the circle using GL_LINE_LOOP (all vertices are connected in a loop)
            glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
        }

        // Unbind the VAO after drawing all spheres
        mSphereVAO->Unbind();


        // Clear the lists after drawing
        mLines.clear();
        mBoxes.clear();
        mSpheres.clear();
    }

}

// Clean up resources when closing the DebugDraw
void DebugDraw::Close()
{
    if (mEngine->isEditorMode())
    {
        delete mShader;
        mShader = nullptr;

        delete mLineVAO;
        mLineVAO = nullptr;

        delete mCubeVAO;
        mCubeVAO = nullptr;
    }
}

// Add a line to the drawing queue
void DebugDraw::DrawLine(const Vector3& start, const Vector3& end, const Color& color, float lineThickness)
{
    if(mEngine->isEditorMode()) mLines.push_back({ start, end, color, lineThickness });
}

// Add a box (cube) to the drawing queue
void DebugDraw::DrawBox(const Vector3& center, const Vector3& extents, const Color& color, float lineThickness, const Quaternion& rotation)
{
    if(mEngine->isEditorMode()) mBoxes.push_back({ center, extents, color, rotation, lineThickness });
}

// Function to draw spheres will go here if implemented in the future
void DebugDraw::DrawSphere(const Vector3& center, float radius, const Color& color, float lineThickness)
{
    if(mEngine->isEditorMode()) mSpheres.push_back({ center,radius,color, lineThickness });
}

#include "pch.h"
#include <Graphics/Sprite/SpriteBatch.h>
#include <Core/ActorComponent/Components/Graphics/SpriteComponent.h>
#include <iostream>

using namespace clt;

SpriteBatch::SpriteBatch(Texture& texture) : mTexture(texture)
{
    // set up vertex data
    GLfloat vertices[] = {
        // first triangle
    // Positions     // UV
    -0.5f,  0.5f,   0.0f, 1.0f, // bottom-left
     0.5f,  0.5f,   1.0f, 1.0f, // bottom-right
     0.5f, -0.5f,   1.0f, 0.0f, // top-right
    -0.5f, -0.5f,   0.0f, 0.0f  // top-left
    };

    constexpr unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
    };


    mVAO = new VertexArray(vertices, 4, indices, 6);
}

SpriteBatch::~SpriteBatch()
{
    delete mVAO;
}

void SpriteBatch::AddSprite(SpriteComponent* comp)
{
    mComponents.emplace_back(comp);
}

void SpriteBatch::RemoveSprite(SpriteComponent* comp)
{
    auto it = std::find(mComponents.begin(), mComponents.end(), comp);
    if (it != mComponents.end())
    {
        mComponents.erase(it);
    }
}

void SpriteBatch::Draw(Shader& pShader)
{
    mTexture.Bind();
    mVAO->Bind();

    for (SpriteComponent* comp : mComponents)
    {
        glm::mat4 tempTransform = comp->GetTransform();
        pShader.SetMat4("model", tempTransform);
        glDrawElements(GL_TRIANGLES, mVAO->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }

    mVAO->Unbind();
    mTexture.UnBind();
}

void SpriteBatch::EndDraw()
{
}

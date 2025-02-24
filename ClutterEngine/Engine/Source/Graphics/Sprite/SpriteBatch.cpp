#include "pch.h"
#include <Graphics/Sprite/SpriteBatch.h>
#include <Core/ActorComponent/Components/Graphics/SpriteComponent.h>
#include <iostream>

using namespace clt;

SpriteBatch::SpriteBatch(Texture* texture) : mTexture(texture)
{
    // set up vertex data
    GLfloat vertices[] = {
        // first triangle
             // pos         // coords
            -0.5f, -0.5f,   0.0f,  0.0f, // bot left 
             0.5f,  0.5f,   1.0f,  1.0f, // top right 
            -0.5f,  0.5f,   0.0f,  1.0f, // top left 

             // pos         // coords
            -0.5f, -0.5f,   0.0f,  0.0f, // bot left 
             0.5f, -0.5f,   1.0f,  0.0f, // bot right 
             0.5f,  0.5f,   1.0f,  1.0f  // top right 
    };

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

SpriteBatch::~SpriteBatch()
{
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
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
    mTexture->Bind();

    glBindVertexArray(mVAO);

    for (SpriteComponent* comp : mComponents)
    {
        glm::mat4 tempTransform = comp->GetTransform();
        pShader.SetMat4("model", tempTransform);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    glBindVertexArray(0);
    mTexture->UnBind();
}

void SpriteBatch::EndDraw()
{
}

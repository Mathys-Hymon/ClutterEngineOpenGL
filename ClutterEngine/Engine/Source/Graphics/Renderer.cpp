#include "pch.h"  
#include <glad/glad.h>
#include<Graphics/Renderer.h>  
#include<Core/ActorComponent/Actor.h>  
#include<Core/ActorComponent/Components/Graphics/SpriteComponent.h>
#include<Graphics/Shader.h>

using namespace clt;

Renderer::Renderer() : mVBO(0), mVAO(0), mAttribSize(0)
{  
   // Initialize GLAD to load OpenGL functions  
   if (gladLoadGL()) CLUTTER_LOG("GLAD initialised successfully")  
   else CLUTTER_ERROR("Cant initialise GLAD");  

   Assets::Get().SetRenderer(this);

   // File paths for vertex and fragment shaders  
   const auto vert_file_path = "Content/Shaders/sprite.vert";
   const auto frag_file_path = "Content/Shaders/sprite.frag";

   mShader = Shader();

   mShader.Load(vert_file_path, frag_file_path);
   mShader.Use();

   // set up vertex data
   GLfloat vertices[] = {
       // first triangle
           // pos         // coords
           -0.5f, -0.5f,   0.0f,  0.0f, // bot left 
            0.5f,  0.5f,   1.0f,  1.0f, // top right 
           -0.5f,  0.5f,   0.0f,  1.0f, // top left 
           // second triangle
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
}  

Renderer::~Renderer()  
{  
   Assets::Get().ClearTextures();  
}  

void Renderer::RegisterTextureUsage(Texture* pTexture)  
{  
   mBindedTextures.insert(pTexture);  
}  

void Renderer::AddGraphicComponent(GraphicComponent* pComp)  
{  
   int compDrawOrder = pComp->GetDrawOrder();  

   if (!mComponents.empty())  
   {  
       std::vector<GraphicComponent*>::iterator gc;  
       for (gc = mComponents.begin(); gc != mComponents.end(); gc++)  
       {  
           if (compDrawOrder < (*gc)->GetDrawOrder()) break;  
       }  
       mComponents.insert(gc, pComp);  
   }  
   else  
   {  
       mComponents.emplace_back(pComp);  
   }  
}  

void Renderer::RemoveGraphicComponent(GraphicComponent* pComp)  
{  
   std::vector<GraphicComponent*>::iterator gc;  
   gc = std::find(mComponents.begin(), mComponents.end(), pComp);  
   mComponents.erase(gc);  
}  

void Renderer::BeginDraw()  
{  
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);         // Define the background Color  
   glClear(GL_COLOR_BUFFER_BIT);                 // Clear the background color and depth  

   for (Texture* tex : mBindedTextures)  
   {  
       tex->Bind();  
   }  
}  

void Renderer::Draw()
{  
    mShader.Use();

    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

   for (GraphicComponent* comp : mComponents)  
   {  
       comp->Draw(*this);  
   }  
}  

void Renderer::DrawSprite(const Actor& pActor, const Texture& pTexture, CRectangle pRect, Vector2 pOrigin) const  
{  
}  

void Renderer::EndDraw()  
{
   for (Texture* tex : mBindedTextures)  
   {  
       tex->UnBind();  
   }  
}
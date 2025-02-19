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
}  

Renderer::~Renderer()  
{  
    // Nettoyer les SpriteBatch
    for (auto& pair : mSpriteBatches)
    {
        delete pair.second;
    }
    mSpriteBatches.clear();

   Assets::Get().ClearTextures();  
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

void Renderer::AddSpriteComponent(SpriteComponent* pComp)
{
    Texture* tex = &pComp->GetTexture();

    if (mSpriteBatches.find(tex) == mSpriteBatches.end())
    {
        mSpriteBatches[tex] = new SpriteBatch(tex);
    }

    mSpriteBatches[tex]->AddSprite(pComp);
}

void Renderer::RemoveSpriteComponent(SpriteComponent* pComp)
{
    Texture* tex = &pComp->GetTexture();

    if (mSpriteBatches.find(tex) != mSpriteBatches.end())
    {
        mSpriteBatches[tex]->RemoveSprite(pComp);
    }
}

void Renderer::BeginDraw()  
{  
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);         // Define the background Color  
   glClear(GL_COLOR_BUFFER_BIT);                 // Clear the background color and depth  

   mShader.Use();
}  

void Renderer::Draw()
{  
   for (GraphicComponent* comp : mComponents)  
   {  
       comp->Draw(*this);  
   }  

   for (auto& pair : mSpriteBatches)
   {
       pair.second->Draw(mShader);
   }
}  

//void Renderer::DrawSprite(const Actor& pActor, const Texture& pTexture, CRectangle pRect, Vector2 pOrigin) const  
//{  
//}  

void Renderer::EndDraw()  
{
    for (auto& pair : mSpriteBatches)
    {
        pair.second->Draw(mShader);
    }
}
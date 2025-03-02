#include "pch.h"  
#include<Graphics/RendererGL.h>  
#include<Core/ActorComponent/Components/Graphics/SpriteComponent.h>  
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>

using namespace clt;  

RendererGL::RendererGL() : mVBO(0), mVAO(0), mAttribSize(0), mEngine(nullptr)  
{}

bool RendererGL::Initialize(CEngine* pEngine)
{  
    mEngine = pEngine;

   // Initialize GLAD to load OpenGL functions  
   if (gladLoadGL()) CLUTTER_LOG("GLAD initialised successfully")  
   else CLUTTER_ERROR("Cant initialise GLAD");  

   Assets::Get().SetRenderer(this);  

   // File paths for vertex and fragment shaders  
   const auto spriteVertPath = "Content/Shaders/sprite.vert";  
   const auto spriteFragPath = "Content/Shaders/sprite.frag";  

   mShader = Shader();  
   mShader.Load(spriteVertPath, spriteFragPath);

   mUIShader = Shader();

}  

void RendererGL::Close()  
{  
   // clear the SpriteBatch  
   for (auto& pair : mSpriteBatches)  
   {  
       delete pair.second;  
   }  
   mSpriteBatches.clear();  

   Assets::Get().ClearTextures();  
}  

void RendererGL::AddGraphicComponent(GraphicComponent* pComp)  
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

void RendererGL::RemoveGraphicComponent(GraphicComponent* pComp)  
{  
   std::vector<GraphicComponent*>::iterator gc;  
   gc = std::find(mComponents.begin(), mComponents.end(), pComp);  

   if(gc != mComponents.end()) mComponents.erase(gc);
}  

void RendererGL::AddSpriteComponent(SpriteComponent* pComp)  
{  
   Texture* tex = pComp->GetTexture();  

   if (mSpriteBatches.find(tex) == mSpriteBatches.end())  
   {  
       mSpriteBatches[tex] = new SpriteBatch(tex);  
   }  
   mSpriteBatches[tex]->AddSprite(pComp);  
}  

void RendererGL::RemoveSpriteComponent(SpriteComponent* pComp)  
{  
   Texture* tex = pComp->GetTexture();  

   if (mSpriteBatches.find(tex) != mSpriteBatches.end())  
   {  
       mSpriteBatches[tex]->RemoveSprite(pComp);  
   }  
}  

void RendererGL::BeginDraw()  
{  
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);         // Define the background Color  
   glClear(GL_COLOR_BUFFER_BIT);                 // Clear the background color and depth  
   glEnable(GL_BLEND);  
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

   mShader.Use();  
}  

void RendererGL::Draw()  
{  
   CameraComponent* camera = CameraComponent::GetActiveCamera();  

   if (camera)  
   {  
       mShader.SetMat4("view", camera->GetViewMatrix());  
       mShader.SetMat4("projection", camera->GetProjectionMatrix());  
   }  
   else  
   {  
       CLUTTER_WARNING("No main camera active !");  
   }  

   for (GraphicComponent* comp : mComponents)  
   {  
       if(comp->IsActive()) comp->Draw(*this);
   }  

   for (auto& pair : mSpriteBatches)  
   {
       pair.second->Draw(mShader);  
   }  
}  

void RendererGL::EndDraw()  
{  
   for (auto& pair : mSpriteBatches)  
   {  
       pair.second->EndDraw();  
   }  
}
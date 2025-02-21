#include "pch.h"  
#include <glad/glad.h>
#include<Graphics/Renderer.h>  
#include<Core/ActorComponent/Actor.h>  
#include<Core/ActorComponent/Components/Graphics/SpriteComponent.h>
#include <Core/ActorComponent/Components/Graphics/CameraComponent.h>
#include <Core/CEngine.h>
#include <glm/gtc/matrix_transform.hpp>
#include<Graphics/Shader.h>
#include <glm/gtx/string_cast.hpp>

using namespace clt;

Renderer::Renderer(CEngine* pEngine) : mVBO(0), mVAO(0), mAttribSize(0), mEngine(*pEngine)
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
   Texture* tex = pComp->GetTexture();

   if (mSpriteBatches.find(tex) == mSpriteBatches.end())
   {
       mSpriteBatches[tex] = new SpriteBatch(tex);
   }
   mSpriteBatches[tex]->AddSprite(pComp);
}

void Renderer::RemoveSpriteComponent(SpriteComponent* pComp)
{
   Texture* tex = pComp->GetTexture();

   if (mSpriteBatches.find(tex) != mSpriteBatches.end())
   {
       mSpriteBatches[tex]->RemoveSprite(pComp);
   }
}

void Renderer::BeginDraw()  
{  
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);         // Define the background Color  
  glClear(GL_COLOR_BUFFER_BIT);                 // Clear the background color and depth  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  mShader.Use();
}  

void Renderer::Draw()
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
      comp->Draw(*this);  
  }  

  for (auto& pair : mSpriteBatches)
  {
      pair.second->Draw(mShader);
  }
} 

void Renderer::EndDraw()  
{
   for (auto& pair : mSpriteBatches)
   {
       pair.second->Draw(mShader);
   }
}
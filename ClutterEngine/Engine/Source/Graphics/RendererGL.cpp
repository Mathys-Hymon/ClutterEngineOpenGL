#include "pch.h"  
#include<Graphics/RendererGL.h>  
#include<Core/ActorComponent/Components/Graphics/SpriteComponent.h>  
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/CEngine.h>

using namespace clt;  

RendererGL::RendererGL() : mEngine(nullptr)  
{}

bool RendererGL::Initialize(CEngine* pEngine)
{  
    mEngine = pEngine;

   // Initialize GLAD to load OpenGL functions  
   if (gladLoadGL()) CLUTTER_LOG("GLAD initialised successfully")  
   else CLUTTER_ERROR("Cant initialise GLAD");  

   Assets::Get().SetRenderer(this);

   // File paths for vertex and fragment shaders  
   const auto spriteVertPath = "Content/Shaders/transform.vert";  
   const auto spriteFragPath = "Content/Shaders/sprite.frag";  

   mUIShader = Shader();  
   mUIShader.Load(spriteVertPath, spriteFragPath);

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


   mUiVAO = new VertexArray(vertices, 4, indices, 6);

   mUiViewProj = Matrix4Row::CreateSimpleViewProj(pEngine->GetWindow()->GetDimensions().x, 
                                                  pEngine->GetWindow()->GetDimensions().y);

}  

void RendererGL::Close()  
{  
   mSpriteComponents.clear();  

   Assets::Get().ClearTextures();  
   delete mUiVAO;
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
    int compDrawOrder = pComp->GetDrawOrder();

    if (!mSpriteComponents.empty())
    {
        std::vector<SpriteComponent*>::iterator gc;
        for (gc = mSpriteComponents.begin(); gc != mSpriteComponents.end(); gc++)
        {
            if (compDrawOrder < (*gc)->GetDrawOrder()) break;
        }
        mSpriteComponents.insert(gc, pComp);
    }
    else
    {
        mSpriteComponents.emplace_back(pComp);
    }
}  

void RendererGL::RemoveSpriteComponent(SpriteComponent* pComp)  
{  
    std::vector<SpriteComponent*>::iterator gc;
    gc = std::find(mSpriteComponents.begin(), mSpriteComponents.end(), pComp);

    if (gc != mSpriteComponents.end()) mSpriteComponents.erase(gc);
}  

void RendererGL::BeginDraw()  
{  
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);         // Define the background Color  
   glClear(GL_COLOR_BUFFER_BIT);                // Clear the background color and depth  
   glEnable(GL_BLEND);  
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
   glClearDepth(false);

   mUIShader.Use();
}  

void RendererGL::Draw()  
{  
   CameraComponent* camera = CameraComponent::GetActiveCamera();

   if (camera)  
   {  
       mUIShader.SetMat4Row("uViewProj", mUiViewProj);
   }  
   else  
   {  
       CLUTTER_WARNING("No main camera active !");  
   }  

   for (GraphicComponent* comp : mComponents)  
   {  
       if(comp->IsActive()) comp->Draw(*this);
   }  
   mUiVAO->Bind();

   for (auto& comp : mSpriteComponents)
   {
       Matrix4Row tempTransform = comp->GetWorldTransform().GetMat4Transform();
       mUIShader.SetMat4Row("uWorldTransform", tempTransform);
       comp->GetTexture()->Bind();
       glDrawElements(GL_TRIANGLES, mUiVAO->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
   }

   mUiVAO->Unbind();
}  

void RendererGL::EndDraw()  
{  
}
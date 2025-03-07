#include "pch.h"  
#include<Graphics/RendererGL.h>  
#include<Core/ActorComponent/Components/Graphics/Sprite/SpriteComponent.h>  
#include<Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>  
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/Debug/DebugDraw.h>
#include <Core/CEngine.h>

using namespace clt;  

RendererGL::RendererGL() : mEngine(nullptr), mUiVAO(nullptr)
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

   mUIShader.Load(spriteVertPath, spriteFragPath);

   // set up vertex data
   constexpr float vertices[] = {
   -0.5f,  0.5f, 0.0f,            0.0f, 0.0f,       //top left
    0.5f,  0.5f, 0.0f,            1.0f, 0.0f,      //top right
    0.5f, -0.5f, 0.0f,           1.0f, 1.0f,     //bottom right
   -0.5f, -0.5f, 0.0f,           0.0f, 1.0f };  //bottom left

   constexpr unsigned int indices[] = {
   0, 1, 2,
   2, 3, 0
   };

   mUiVAO = new VertexArray(vertices, 4, indices, 6);

   mUiViewProj = Matrix4Row::CreateSimpleViewProj(pEngine->GetWindow()->GetDimensions().x, 
                                                  pEngine->GetWindow()->GetDimensions().y);

   DebugDraw::Get().Start();
}  

void RendererGL::Close()  
{  
   mSpriteComponents.clear();  

   Assets::Get().ClearTextures();  
   delete mUiVAO;
}

void RendererGL::AddMeshComponent(MeshComponent* pComp)
{
    int compDrawOrder = pComp->GetUpdateOrder();

    if (!mMeshComponents.empty())
    {
        std::vector<MeshComponent*>::iterator gc;
        for (gc = mMeshComponents.begin(); gc != mMeshComponents.end(); gc++)
        {
            if (compDrawOrder < (*gc)->GetUpdateOrder()) break;
        }
        mMeshComponents.insert(gc, pComp);
    }
    else
    {
        mMeshComponents.emplace_back(pComp);
    }
}

void RendererGL::RemoveMeshComponent(MeshComponent* pComp)
{
    std::vector<MeshComponent*>::iterator gc;
    gc = std::find(mMeshComponents.begin(), mMeshComponents.end(), pComp);

    if (gc != mMeshComponents.end()) mMeshComponents.erase(gc);
}

void RendererGL::AddSpriteComponent(SpriteComponent* pComp)  
{  
    int compDrawOrder = pComp->GetUpdateOrder();

    if (!mSpriteComponents.empty())
    {
        std::vector<SpriteComponent*>::iterator gc;
        for (gc = mSpriteComponents.begin(); gc != mSpriteComponents.end(); gc++)
        {
            if (compDrawOrder < (*gc)->GetUpdateOrder()) break;
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
   glClearColor(0.45f, 0.45f, 1.0f, 1.0f);       // Define the background Color  
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   glDisable(GL_BLEND);
}  

void RendererGL::Draw()  
{  
    // Get the active camera
    CameraComponent* camera = CameraComponent::GetActiveCamera();
    Matrix4Row viewProj;

    if (camera)  viewProj = camera->GetViewProjMatrices();
    else  CLUTTER_WARNING("No main camera active !");

    for (MeshComponent* comp : mMeshComponents)
    {
        comp->Draw(viewProj);
    }

    DebugDraw::Get().Draw(viewProj);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    mUIShader.Use();

   mUIShader.SetMat4Row("uViewProj", mUiViewProj);
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
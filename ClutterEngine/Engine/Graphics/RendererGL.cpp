#include "pch.h"  
#include<Graphics/RendererGL.h>  
#include<Core/ActorComponent/Components/Graphics/Sprite/SpriteComponent.h>  
#include<Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>  
#include <Graphics/UI/WidgetElement.h>
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/Debug/DebugDraw.h>
#include <Core/CEngine.h>

using namespace clt;

RendererGL::RendererGL() : mEngine(nullptr), mSpriteVAO(nullptr)
{
}

bool RendererGL::Initialize(CEngine* pEngine)
{
    mEngine = pEngine;

    // Initialize GLAD to load OpenGL functions  
    if (gladLoadGL()) CLUTTER_LOG("GLAD initialised successfully")
    else CLUTTER_ERROR("Cant initialise GLAD");

    Assets::Get().SetRenderer(this);
    Assets::Get().LoadTexture("Content/Resources/Sprites/default.png", "default");

    // File paths for vertex and fragment shaders  
    const auto spriteVertPath = "Content/Resources/Shaders/sprite.vert";
    const auto spriteFragPath = "Content/Resources/Shaders/sprite.frag";

    mSpriteShader.Load(spriteVertPath, spriteFragPath);

    const auto textVertPath = "Content/Resources/Shaders/text.vert";
    const auto textFragPath = "Content/Resources/Shaders/text.frag";

    mTextShader.Load(textVertPath, textFragPath);

    constexpr float spriteVertices[] = {
        //POSITION                      NORMALS                     TEXCOORDS
        -0.5f, 0.5f, 0.0f,              0.0f, 0.0f, 0.0f,           0.0f, 0.0f,     //top left
        0.5f, 0.5f, 0.0f,               0.0f, 0.0f, 0.0f,           1.0f, 0.0f,     //top right
        -0.5f, -0.5f, 0.0f,             0.0f, 0.0f, 0.0f,           0.0f, 1.0f,      //bottom left
        0.5f, -0.5f, 0.0f,              0.0f, 0.0f, 0.0f,           1.0f, 1.0f,     //bottom right
    };

    mSpriteVAO = new VertexArray(spriteVertices, 4);
    mTextVAO = new VertexArray(spriteVertices, 4, BufferUsage::DYNAMIC);

    mUiViewProj = Matrix4Row::CreateSimpleViewProj(pEngine->GetWindow()->GetDimensions().x,
        pEngine->GetWindow()->GetDimensions().y);
    DebugDraw::Get().Start();
}

void RendererGL::Close()
{
    mSpriteComponents.clear();

    Assets::Get().ClearTextures();
    delete mSpriteVAO;
}

void RendererGL::WireframeMode(bool wireframe)
{
    if (wireframe)  glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
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

void RendererGL::AddHUDComponent(HUDComponent* pComp)
{
    int compDrawOrder = pComp->GetUpdateOrder();

    if (!mHUD.empty())
    {
        std::vector<HUDComponent*>::iterator gc;
        for (gc = mHUD.begin(); gc != mHUD.end(); gc++)
        {
            if (compDrawOrder < (*gc)->GetUpdateOrder()) break;
        }
        mHUD.insert(gc, pComp);
    }
    else
    {
        mHUD.emplace_back(pComp);
    }
}

void RendererGL::RemoveHUDComponent(HUDComponent* pComp)
{
    std::vector<HUDComponent*>::iterator gc;
    gc = std::find(mHUD.begin(), mHUD.end(), pComp);

    if (gc != mHUD.end()) mHUD.erase(gc);
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
        if (!comp->IsActive()) continue;

        comp->Draw(viewProj);
    }

    DebugDraw::Get().Draw(viewProj);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mSpriteShader.Use();

    mSpriteShader.SetMat4Row("uViewProj", viewProj);
    mSpriteVAO->Bind();

    for (auto& comp : mSpriteComponents)
    {
        if (!comp->IsActive()) continue;

        Matrix4Row tempTransform = comp->GetWorldTransform().GetMat4Transform();
        mSpriteShader.SetMat4Row("uWorldTransform", tempTransform);

        comp->GetTexture()->Bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    mSpriteShader.SetMat4Row("uViewProj", mUiViewProj);

    for (HUDComponent* hud : mHUD)
    {
        for (WidgetElement* element : hud->GetCurrentWidget()->GetElements())
        {
            if (!element->mVisibility) continue;

            Matrix4Row tempTransform = element->GetTransform().To3D().GetMat4Transform();
            mSpriteShader.SetMat4Row("uWorldTransform", tempTransform);

            element->Draw(this);
        }
    }

    mSpriteVAO->Unbind();
}

void RendererGL::BindText(Color textColor)
{
    mTextShader.Use();
    mTextShader.SetVec3f("textColor", textColor);
    mTextShader.SetMat4Row("projection", mUiViewProj);

    glActiveTexture(GL_TEXTURE0);
    mTextVAO->Bind();
}

void RendererGL::EndDraw()
{
}
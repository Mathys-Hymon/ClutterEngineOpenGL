#include "pch.h"  
#include<Graphics/RendererGL.h>  
#include<Core/ActorComponent/Components/Graphics/Sprite/SpriteComponent.h>  
#include<Core/ActorComponent/Components/Graphics/Mesh/MeshComponent.h>  
#include <Graphics/UI/WidgetElement.h>
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>
#include <Core/ActorComponent/ChildActors/EditorCamera.h>
#include <Core/CEngine.h>
#include <GLFW/glfw3.h>

using namespace clt;

RendererGL::RendererGL() : mEngine(nullptr), mSpriteVAO(nullptr)
{
}

void RendererGL::Initialize(CEngine* pEngine, Color backgroundColor)
{
    mBackgroundColor = backgroundColor;
    mEngine = pEngine;

    // Initialize GLAD to load OpenGL functions  
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) CLUTTER_LOG("GLAD initialised successfully");
    else CLUTTER_ERROR("Cant initialise GLAD");

    Assets::Get().SetRenderer(this);

    // File paths for vertex and fragment shaders  
    const auto spriteVertPath = "Content/Resources/Shaders/sprite.vert";
    const auto spriteFragPath = "Content/Resources/Shaders/sprite.frag";

    mSpriteShader.Compose({ 
        Assets::Get().LoadShader(spriteVertPath, ShaderType::VERTEX),
        Assets::Get().LoadShader(spriteFragPath, ShaderType::FRAGMENT), 
        });

    const auto textVertPath = "Content/Resources/Shaders/text.vert";
    const auto textFragPath = "Content/Resources/Shaders/text.frag";

    mTextShader.Compose({ 
        Assets::Get().LoadShader(textVertPath, ShaderType::VERTEX),
        Assets::Get().LoadShader(textFragPath, ShaderType::FRAGMENT),
        });

    constexpr float spriteVertices[] = 
    {
        //POSITION                      NORMALS                     TEXCOORDS
        -0.5f, 0.5f, 0.0f,              0.0f, 0.0f, 0.0f,           0.0f, 0.0f,     //top left
        0.5f, 0.5f, 0.0f,               0.0f, 0.0f, 0.0f,           1.0f, 0.0f,     //top right
        -0.5f, -0.5f, 0.0f,             0.0f, 0.0f, 0.0f,           0.0f, 1.0f,      //bottom left
        0.5f, -0.5f, 0.0f,              0.0f, 0.0f, 0.0f,           1.0f, 1.0f,     //bottom right
    };

    mSpriteVAO = new VertexArray(spriteVertices, 4);

    Vector2 windowSize = Window::Get().GetDimensions();

    mUiViewProj = Matrix4Row::CreateOrtho(windowSize.x, windowSize.y, -1, 100000);

    mTextShader.Use();
    mTextShader.SetMat4Row("uViewProj", mUiViewProj);
    mSpriteShader.Use();
    mSpriteShader.SetMat4Row("uViewProj", mUiViewProj);
    glPatchParameteri(GL_PATCH_VERTICES, 3);

}

void RendererGL::Close()
{
    mSpriteComponents.clear();

    Assets::Get().ClearAssets();
    delete mSpriteVAO;
}

void RendererGL::WireframeMode(bool wireframe)
{
    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    mWireframe = wireframe;
}

void RendererGL::ToggleWireframe()
{
    glPolygonMode(GL_FRONT_AND_BACK, !mWireframe ? GL_LINE : GL_FILL);
    mWireframe = !mWireframe;
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

    if (gc != mMeshComponents.end())
    {
        mMeshComponents.erase(gc);
    }
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
    glClearColor(mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);       // Define the background Color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
}

void RendererGL::Draw()
{
    // Get the active camera
    CameraComponent* camera = CameraComponent::GetActiveCamera();
    Matrix4Row viewProj;

    if (camera)  viewProj = camera->GetViewProjMatrices();
    else
    {
        mEngine->GetLevelManager()->GetCurrentLevel()->AddActor<EditorCamera>();
    }

    for (MeshComponent* comp : mMeshComponents)
    {
        if (!comp->IsActive()) continue;

        comp->Draw(viewProj);
    }

    mSpriteShader.Use();

    mSpriteShader.SetMat4Row("uViewProj", viewProj);
    mSpriteVAO->Bind();

    for (SpriteComponent* comp : mSpriteComponents)
    {
        if (!comp->IsActive()) continue;

        Matrix4Row tempTransform = comp->GetWorldTransform().GetMat4Transform();

        mSpriteShader.SetBool("uFlipX", comp->GetFlipX());
        mSpriteShader.SetBool("uFlipY", comp->GetFlipY());
        mSpriteShader.SetMat4Row("uWorldTransform", tempTransform);

        comp->GetTexture().lock()->Bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mSpriteShader.SetBool("uFlipX", false);
    mSpriteShader.SetBool("uFlipY", true);

    mSpriteShader.SetMat4Row("uViewProj", mUiViewProj);

    for (HUDComponent* hud : mHUD)
    {
        for (WidgetElement* element : hud->GetCurrentWidget()->GetElements())
        {
            if (!element->mVisibility) continue;
            mSpriteVAO->Bind();
            mSpriteShader.Use();

            Matrix4Row tempTransform = element->GetTransform().To3D().GetMat4Transform();
            mSpriteShader.SetMat4Row("uWorldTransform", tempTransform);
            element->Draw(this);
        }
    }

    mSpriteVAO->Unbind();
}

void RendererGL::EndDraw()
{
}
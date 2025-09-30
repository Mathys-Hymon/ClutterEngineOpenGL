#pragma once
#include <Core/CEngine.h>
#include <Editor/ImGuiLayer.h>
#include <Graphics/FrameBuffer/FrameBuffer.h>
#include <Core/ActorComponent/Components/Graphics/Camera/CameraComponent.h>

namespace clt
{
    enum class CLUTTER_API EditorMode
    {
        InGame,
        Paused,
        InEditor,
    };

    class EditorViewport;
    class Level;
    class CLUTTER_API EditorApplication 
    {

    protected:
        std::unique_ptr<clt::CEngine> mEngine;
        std::unique_ptr<ImGuiLayer> mEditor;

        Actor* mEditorCam;
        CameraComponent* mInGameCam;
        FrameBuffer* mViewportFramebuffer;
        EditorMode mMode;
        bool mFirstEditor;

        void Init(std::vector<clt::Level*> pLevels, const std::string& configFile = "Config/project.config.json");

        void Run();

        virtual void Update();

        virtual void Render();

        void ShowWireframe();
        void ShowLitMode();

        void SetCamera(bool inGame);

    public:

        EditorApplication(std::vector<clt::Level*> pLevels, const std::string& configFile = "Config/project.config.json");
        ~EditorApplication();

        RendererGL* GetRenderer() const { return mEngine->GetRenderer(); }

        CEngine& GetEngine() const { return *mEngine.get(); }

        EditorMode GetMode() const { return mMode; };
        void SetMode(EditorMode mode);

        friend EditorViewport;
    };
}

#pragma once
#include <memory>
#include <vector>
#include <string>

#include <Core/CEngine.h>
#include <Editor/UI/EditorUIManager.h>
#include <Editor/Services/ImGuiContextService.h>
#include <Editor/Services/EditorContext.h>

namespace clt
{
    enum class CLUTTER_API EditorMode
    {
        InGame,
        Paused,
        InEditor,
    };

    class Level;
    class Actor;
    class CameraComponent;
    
    class CLUTTER_API EditorApplication
    {
        protected:
        virtual void Update();
        virtual void Render();
        
        void Init(std::vector<clt::Level*> pLevels, const std::string& configFile);
        void SetupEditor();
        void SetCamera(bool inGameMode);
        void RegisterDefaultPanels();
        
        // Engine
        std::unique_ptr<CEngine> mEngine;
        
        // Editor
        std::unique_ptr<editor::ImGuiContextService> mImGuiService;
        std::unique_ptr<editor::EditorContext> mEditorCtx;
        std::unique_ptr<editor::EditorUIManager> mUIManager;
        std::unique_ptr<editor::PanelManager> mPanelManager;
        
        // State
        EditorMode mMode{EditorMode::InEditor};
        Actor* mEditorCam{nullptr};
        CameraComponent* mInGameCam{nullptr};
        
    public:
        EditorApplication(std::vector<clt::Level*> pLevels, const std::string& configFile = "Config/project.config.json");
        virtual ~EditorApplication();
        
        void Run();
        
        CEngine& GetEngine() const { return *mEngine; };
        IRenderer* GetRenderer() const { return mEngine->GetRenderer(); }
        EditorMode GetMode() const { return mMode; }
        
        void SetMode(EditorMode mode);
    };
}

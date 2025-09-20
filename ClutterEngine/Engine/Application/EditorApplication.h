#pragma once
#include <Core/CEngine.h>
#include <Editor/ImGuiLayer.h>

namespace clt
{
    class Level;
    class CLUTTER_API EditorApplication {

    protected:
        std::unique_ptr<clt::CEngine> mEngine;
        std::unique_ptr<ImGuiLayer> mEditor;

        void Init(std::vector<clt::Level*> pLevels, const std::string& configFile = "Config/project.config.json");

        void Run();

        virtual void Update();

        virtual void Render();

        void ShowWireframe();
        void ShowLitMode();

    public:

        EditorApplication(std::vector<clt::Level*> pLevels, const std::string& configFile = "Config/project.config.json");
        ~EditorApplication();

        clt::RendererGL* GetRenderer() const { return mEngine->GetRenderer(); }
    };
}

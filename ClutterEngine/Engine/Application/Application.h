#pragma once
#include <Core/CEngine.h>

namespace clt
{
    class Level;
    class CLUTTER_API Application {
        
        std::unique_ptr<CEngine> mEngine;

        void Run();

        void Update();

        void Render();

        void ShowWireframe();
        void ShowLitMode();

    public:

        Application(std::vector<Level*> pLevels, const std::string& configFile = "Config/project.config.json");
        ~Application();

        Window* GetWindow() const { return mEngine->GetWindow(); }
        RendererGL* GetRenderer() const { return mEngine->GetRenderer(); }
    };
}
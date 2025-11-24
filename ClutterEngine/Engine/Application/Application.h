#pragma once
#include <Core/CEngine.h>

namespace clt
{
    class Level;
    class CLUTTER_API Application {

    protected:
        std::unique_ptr<CEngine> mEngine;

        Application() = default;

        void Init(std::vector<Level*> pLevels, const std::string& configFile = "Config/project.config.json");

        void Run();

        virtual void Update();

        virtual void Render();

        void ShowWireframe();
        void ShowLitMode();

    public:

        Application(std::vector<Level*> pLevels, const std::string& configFile = "Config/project.config.json");
        ~Application();

        IRenderer* GetRenderer() const { return mEngine->GetRenderer(); }
    };
}
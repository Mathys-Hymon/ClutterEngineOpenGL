#pragma once
#include <Core/CEngine.h>

    class Level;
    class EditorApplication {

    protected:
        std::unique_ptr<clt::CEngine> mEngine;

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
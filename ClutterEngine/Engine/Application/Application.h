#pragma once
#include <Core/CEngine.h>

namespace clt
{
    class Level;
    class CLUTTER_API Application {

        void Run();

        void Update();

        void Render();

        void ShowWireframe();
        void ShowLitMode();

    public:

        Application(std::vector<Level*> pLevels, const std::string& configFile = "Config/project.config.json");
        ~Application();
    };
}
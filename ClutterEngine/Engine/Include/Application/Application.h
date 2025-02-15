#pragma once
#include <Core/CEngine.h>

namespace clt
{
    class CLUTTER_API Application {
        
        std::string mName;
        std::unique_ptr<CEngine> mEngine;

        void Init(int pWidth, int pHeight, std::string pName);

        void Run();

        void Update();

        void Render();

    public:

        Application(int pWidth = 800, int pHeight = 600, std::string pName = "Clutter Editor");
        ~Application();

        void Close();

        Window* GetWindow() const { return mEngine->GetWindow(); }
        Renderer* GetRenderer() const { return mEngine->GetRenderer(); }
    };
}

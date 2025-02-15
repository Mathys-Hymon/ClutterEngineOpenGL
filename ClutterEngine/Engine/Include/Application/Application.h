#pragma once
#include <Window/Window.h>

namespace clt
{
    class CLUTTER_API Application {
        
        std::string mName;
        std::unique_ptr<Window> mWindow;

        void Init(int pWidth, int pHeight, std::string pName);

        void Run();

        void Update();

        void Render();

    public:

        Application(int pWidth, int pHeight, std::string pName = "Clutter Editor");
        ~Application();

        void Close();

        Window* GetWindow() const { return mWindow.get(); }
    };
}

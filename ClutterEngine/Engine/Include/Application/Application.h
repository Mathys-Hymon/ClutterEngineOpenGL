#pragma once
#include <Window/Window.h>

namespace clt
{
    class CLUTTER_API Application {
    public:
        Application(int pWidth, int pHeight, std::string pName);
        ~Application();

        void Shutdown();

        Window* GetWindow() { return mWindow; }

    private:
        void Init(int width, int height, std::string name);
        void Run();

        void Tick();
        void Render();

        Window* mWindow = nullptr;
    };
}

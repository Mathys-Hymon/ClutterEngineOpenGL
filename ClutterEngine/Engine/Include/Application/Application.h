#pragma once
#include <Window/Window.h>

namespace clt
{
    class CLUTTER_API Application {
    public:
        Application(int width, int height, std::string name);
        void Run();
        Window* GetWindow() { return mWindow; }
        ~Application();
    private:
        void Init(int width, int height, std::string name);
        void Shutdown();
        Window* mWindow = nullptr;
    };
}

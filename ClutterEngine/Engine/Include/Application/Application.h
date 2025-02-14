#pragma once
#include <Window/Window.h>

namespace clt
{
    class CLUTTER_API Application {
    public:
        Application(int pWidth, int pHeight, std::string pName);
        virtual ~Application();

        void Shutdown();

        Window* GetWindow() const { return mWindow; }
        void Run();

    protected:
        void Init(int width, int height, std::string name);

        virtual void Update() = 0;
        virtual void Render() = 0;

        Window* mWindow = nullptr;
    };
}

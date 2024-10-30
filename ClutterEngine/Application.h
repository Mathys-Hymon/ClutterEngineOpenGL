#ifdef CLUTTERENGINE_EXPORTS
#define CLUTTERENGINE_API __declspec(dllexport)
#else
#define CLUTTERENGINE_API __declspec(dllimport)
#endif

#include "Window.h"

class CLUTTERENGINE_API Application {
public:
    Application(int width, int height, std::string name);
    void Run();
	Window* GetWindow() { return window; }
    ~Application();
private:
    void Init(int width, int height, std::string name);
    void Shutdown();
    Window* window = nullptr;
};
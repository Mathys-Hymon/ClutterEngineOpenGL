#ifdef CLUTTERENGINE_EXPORTS
#define CLUTTERENGINE_API __declspec(dllexport)
#else
#define CLUTTERENGINE_API __declspec(dllimport)
#endif

#include "Window.h"

class CLUTTERENGINE_API Application {
public:
    Application();
    void Run();
    ~Application();
private:
    void Init();
    void Shutdown();
    Window* window = nullptr;
};
#ifdef CLUTTERENGINE_EXPORTS
#define CLUTTERENGINE_API __declspec(dllexport)
#else
#define CLUTTERENGINE_API __declspec(dllimport)
#endif
#include <string>
#include <iostream>

class CLUTTERENGINE_API Window {
public:
    Window(unsigned int width, unsigned int height, const std::string& title);
    ~Window();
    bool ShouldClose() const;
    void SwapBuffers() const;
};
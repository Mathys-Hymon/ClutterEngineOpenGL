
#ifdef CLUTTERENGINE_EXPORTS
#define CLUTTERENGINE_API __declspec(dllexport)
#else
#define CLUTTERENGINE_API __declspec(dllimport)
#endif

#include <string>


class CLUTTERENGINE_API Window {
public:
    Window(unsigned int width, unsigned int height, const std::string& title);
//	GLFWwindow* getRef() const;
	void ResizeViewport(unsigned int startWidth,unsigned int startHeight, unsigned int width, unsigned int height);
    bool ShouldClose() const;
    void SwapBuffers() const;
    ~Window();

};
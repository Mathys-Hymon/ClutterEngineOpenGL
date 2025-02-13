#pragma once
#include <Core/CCommon.h>

class GLFWwindow;

namespace clt
{
    class CLUTTER_API Window {
    public:
        Window(uint32 pWidth, uint32 pHeight,std::string pName = "Clutter Engine");
        Window(const Window&) = delete;

        ~Window();

        void operator=(const Window&) = delete;

        inline Vector2 GetDimensions() const { return mDimensions; };
        inline GLFWwindow* GetGLFWWindow() const { return mGlfwWindow; }

        void ResizeViewport(unsigned int startWidth, unsigned int startHeight, unsigned int width, unsigned int height);
        bool ShouldClose() const;
        void SwapBuffers() const;

        void Close();

    private:

        GLFWwindow* mGlfwWindow;
        Vector2 mDimensions;
        std::string mName;
    };
}

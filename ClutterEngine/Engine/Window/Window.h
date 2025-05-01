#pragma once
#include <Core/CCommon.h>
#include "Core/Maths/Vectors/Vector2.h"

class GLFWwindow;

namespace clt
{

    class CEngine;
    class CLUTTER_API Window 
    {

        Window() = default;

        void InternalInit(u32 width, u32 height, const std::string& name, bool vsync);

        GLFWwindow* mGlfwWindow = nullptr;
        Vector2 mDimensions = { 0.f, 0.f };
        bool mIsInitialized = false;

        friend class CEngine;

    public:

        static Window& Get();

        Window(const Window&) = delete;
        void operator=(const Window&) = delete;

        ~Window();

        Vector2 GetDimensions() const { return mDimensions; }
        GLFWwindow* GetGLFWWindow() const { return mGlfwWindow; }

        void ResizeViewport(unsigned int startWidth, unsigned int startHeight, unsigned int width, unsigned int height);
        void RenameViewport(const char* name);
        bool ShouldClose() const;
        void SwapBuffers() const;
        void Close();
    };
}

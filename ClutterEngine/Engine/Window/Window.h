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

        GLFWwindow* mGlfwWindow = nullptr;
        Vector2 mDimensions = { 0.f, 0.f };
        bool mIsInitialized = false;
        std::string mName = "";

        friend class CEngine;

    public:

        static Window& Get();
        void InternalInit(u32 width, u32 height, const std::string& name, bool vsync, u32 xStart = 0, u32 xEnd = -1, u32 yStart = 0, u32 yEnd = -1);

        Window(const Window&) = delete;
        void operator=(const Window&) = delete;

        ~Window();

        Vector2 GetDimensions() const { return mDimensions; }
        GLFWwindow* GetGLFWWindow() const { return mGlfwWindow; }
        std::string GetName() const { return mName; };

        void ResizeViewport(u32 startWidth, u32 startHeight, u32 width, u32 height);
        void ResizeViewportCentered(u32 width, u32 height);
        void RenameViewport(const char* name);
        bool ShouldClose() const;
        void SwapBuffers() const;
        void Close();
    };
}

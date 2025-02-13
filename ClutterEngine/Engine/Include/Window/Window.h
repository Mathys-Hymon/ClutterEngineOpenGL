#pragma once
#include <Core/CCommon.h>

namespace clt
{
    class CLUTTER_API Window {
    public:
        Window(unsigned int width, unsigned int height, const std::string& title);
        ~Window();

        void ResizeViewport(unsigned int startWidth, unsigned int startHeight, unsigned int width, unsigned int height);
        bool ShouldClose() const;
        void SwapBuffers() const;
    };
}

#pragma once
#include "functional"

namespace clt
{
    namespace editor
    {
        class CLUTTER_API ImGuiContextService
        {
            const char* mGLSL{nullptr};
        public:
            ImGuiContextService(const char* glsl_version = "#version 460");
            ~ImGuiContextService();
    
            void NewFrame();
            void Render();
    
            // allow ThemeManager to apply styles (lambda will call SetEditorTheme)
            void ApplyStyle(const std::function<void()>& applyTheme);
        };

    }
}

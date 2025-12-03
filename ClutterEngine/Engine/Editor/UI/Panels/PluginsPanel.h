#pragma once
#include <Core/CCommon.h>
#include <Editor/UI/EditorPanel.h>

namespace clt
{
    namespace editor
    {
        class CLUTTER_API PluginsPanel : public EditorPanel
        {
        public :
            PluginsPanel(EditorContext* context);
            const char* GetName() const override;
            void Draw() override;
        };
    }
}
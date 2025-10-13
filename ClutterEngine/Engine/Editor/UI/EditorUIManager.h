#pragma once
#include <Core/CCommon.h>
#include <Editor/UI/IEditorPanel.h>
#include <Editor/EditorContext.h>

namespace clt
{
	namespace editor
	{
        class EditorUIManager {
            std::vector<std::unique_ptr<IEditorPanel>> panels;
            EditorContext* ctx;

        public:
            EditorUIManager(EditorContext* context) : ctx(context) {}

            void RegisterPanel(std::unique_ptr<IEditorPanel> panel);

            void DrawAll();
        };
	}
}
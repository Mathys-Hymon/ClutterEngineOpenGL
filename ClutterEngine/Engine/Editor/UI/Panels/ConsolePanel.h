#pragma once
#include <Core/CCommon.h>
#include <Editor/UI/IEditorPanel.h>
#include <Editor/EditorContext.h>

namespace clt
{
	namespace editor
	{
		class CLUTTER_API ConsolePanel : public IEditorPanel
		{
			EditorContext* ctx;

		public:
			ConsolePanel(EditorContext* context);
			const char* GetName() const override;
			void Draw() override;
		};
	}
}
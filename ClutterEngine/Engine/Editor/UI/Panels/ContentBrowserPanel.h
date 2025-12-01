#pragma once
#include <Core/CCommon.h>
#include <Editor/UI/IEditorPanel.h>

namespace clt
{
	namespace editor
	{
		class CLUTTER_API ContentBrowserPanel : public IEditorPanel
		{
			EditorContext* ctx;

		public:
			ContentBrowserPanel(EditorContext* context);
			const char* GetName() const override;
			void Draw() override;
		};
	}
}
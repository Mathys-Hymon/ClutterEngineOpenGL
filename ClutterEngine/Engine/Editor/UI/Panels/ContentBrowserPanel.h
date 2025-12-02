#pragma once
#include <Core/CCommon.h>
#include <Editor/UI/EditorPanel.h>

namespace clt
{
	namespace editor
	{
		class CLUTTER_API ContentBrowserPanel : public EditorPanel
		{
			EditorContext* ctx;

		public:
			ContentBrowserPanel(EditorContext* context);
			const char* GetName() const override;
			void Draw() override;
		};
	}
}
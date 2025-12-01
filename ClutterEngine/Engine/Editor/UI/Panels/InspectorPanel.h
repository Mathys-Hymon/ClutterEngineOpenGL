#pragma once
#include <Core/CCommon.h>
#include <Editor/UI/IEditorPanel.h>

namespace clt
{
	namespace editor
	{
		class CLUTTER_API InspectorPanel : public IEditorPanel
		{
			EditorContext* ctx;

		public:
			InspectorPanel(EditorContext* context);
			const char* GetName() const override;
			void Draw() override;
		};
	}
}
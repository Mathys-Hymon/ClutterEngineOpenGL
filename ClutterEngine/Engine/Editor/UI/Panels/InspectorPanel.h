#pragma once
#include <Core/CCommon.h>
#include <Editor/UI/EditorPanel.h>

namespace clt
{
	namespace editor
	{
		class CLUTTER_API InspectorPanel : public EditorPanel
		{
		public:
			InspectorPanel(EditorContext* context);
			const char* GetName() const override;
			DockPosition GetDockingPos() const override;
			void Draw() override;
		};
	}
}
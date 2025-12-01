#pragma once
#include <Core/CCommon.h>
#include <Editor/Services/EditorContext.h>

namespace clt
{
	namespace editor
	{
		class CLUTTER_API IEditorPanel
		{
		public:
			virtual ~IEditorPanel() = default;

			// label visible in UI ("Console")
			virtual const char* GetName() const = 0;

			// stable internal id ("clt.panel.console") - used for layout / collisions / serialization
			virtual std::string GetID() const { return std::string(GetName()); }

			// ImGui window flags for this panel
			virtual int GetWindowFlags() const { return 0; }

			// lifecycle
			virtual void OnAttach() {}
			virtual void OnDetach() {}

			// draw content only (NO ImGui::Begin/End here)
			virtual void Draw() = 0;
		};
	}
}
#pragma once
#include <Core/CCommon.h>
#include <Editor/Services/EditorContext.h>

namespace clt
{
	namespace editor
	{
		class CLUTTER_API EditorPanel
		{
			bool mIsOpen{true};
			
		public:
			// label visible in UI ("Console")
			virtual const char* GetName() const = 0;

			// stable internal id ("clt.panel.console") - used for layout / collisions / serialization
			virtual std::string GetID() const { return std::string(GetName()); }

			// ImGui window flags for this panel
			virtual int GetWindowFlags() const { return 0; }

			void Toggle() { mIsOpen = !mIsOpen; }
			void SetOpen(bool newOpen) { mIsOpen = newOpen; }
			bool IsOpen() const { return mIsOpen; }
			
			// draw content only (NO ImGui::Begin/End here)
			virtual void Draw() = 0;
		};
	}
}
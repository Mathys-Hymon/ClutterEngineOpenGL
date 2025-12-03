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
			bool mWasOpen{false};
			bool mIsDocked{false};
			
		protected:
			EditorContext* ctx{nullptr};
			
			bool Begin();
			void End();
		public:
			EditorPanel(EditorContext* Context) : ctx(Context) {};
			// label visible in UI ("Console")
			virtual const char* GetName() const = 0;

			// draw content only (NO ImGui::Begin/End here)
			virtual void Draw() = 0;
			
			// stable internal id ("clt.panel.console") - used for layout / collisions / serialization
			virtual std::string GetID() const { return std::string(GetName()); }

			// ImGui window flags for this panel
			virtual int GetPanelFlags() const { return 0; }

			void Open() { mIsOpen = true; }
			void Close()
			{
				mIsOpen = false;
				mWasOpen = false;
			}
			void Toggle()
			{
				mIsOpen = !mIsOpen;
				mWasOpen = mIsOpen;
			}
			bool IsOpen() const { return mIsOpen; }
			
			friend class EditorUIManager;
		};
	}
}
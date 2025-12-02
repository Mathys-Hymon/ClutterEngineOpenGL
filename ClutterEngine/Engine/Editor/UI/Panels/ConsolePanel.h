#pragma once
#include <Core/CCommon.h>
#include <Editor/UI/EditorPanel.h>

namespace clt
{
	namespace editor
	{
		class CLUTTER_API ConsolePanel : public EditorPanel
		{
			EditorContext* ctx;
			
			bool mShowInfo{false};
			bool mShowLog{false};
			bool mShowWarning{false};
			bool mShowError{false};

		public:
			ConsolePanel(EditorContext* context);
			const char* GetName() const override;
			void Draw() override;
		};
	}
}
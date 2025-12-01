#pragma once
#include <unordered_map>
#include <Core/CCommon.h>
#include "IEditorPanel.h"

namespace clt
{
	namespace editor
	{
		class CLUTTER_API PanelManager
		{
		public:
			using PanelPtr = std::shared_ptr<IEditorPanel>;
			
		private:
			std::vector<PanelPtr> mPanels;
			std::unordered_map<std::string, IEditorPanel*> mPanelsById;
			std::unordered_map<IEditorPanel*, std::string> mIdOverrides;
			
		public:
			void RegisterPanel(PanelPtr panel);
			
			const std::vector<PanelPtr>& GetPanels() const { return mPanels; }
			
			IEditorPanel* FindByID(const std::string& id) const;
			std::string GetRegisteredID(IEditorPanel* panel) const;
			
		};
	}
}
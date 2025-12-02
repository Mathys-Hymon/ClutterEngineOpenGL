#pragma once
#include <unordered_map>
#include <Core/CCommon.h>
#include "EditorPanel.h"

namespace clt
{
	namespace editor
	{
		class CLUTTER_API PanelManager
		{
		public:
			using PanelPtr = std::shared_ptr<EditorPanel>;
			
		private:
			std::vector<PanelPtr> mPanels;
			std::unordered_map<std::string, EditorPanel*> mPanelsById;
			std::unordered_map<EditorPanel*, std::string> mIdOverrides;
			
		public:
			void RegisterPanel(PanelPtr panel);
			
			const std::vector<PanelPtr>& GetPanels() const { return mPanels; }
			
			EditorPanel* FindByID(const std::string& id) const;
			std::string GetRegisteredID(EditorPanel* panel) const;
			
		};
	}
}
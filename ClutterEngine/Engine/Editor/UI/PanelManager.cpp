#include "pch.h"
#include "PanelManager.h"

void clt::editor::PanelManager::RegisterPanel(PanelPtr panel)
{
    if (!panel) return;
    std::string id = panel->GetID();
			
    if (mPanelsById.find(id) != mPanelsById.end())
    {
        int n = 1;
        std::string newId;
				
        do{
            newId = id + "_" + std::to_string(n);
        } while (mPanelsById.find(newId) != mPanelsById.end());
				
        mPanelsById[newId] = panel.get();
        mPanels.push_back(std::move(panel));
        mIdOverrides[mPanels.back().get()] = newId;
    }
    else
    {
        mPanelsById[id] = panel.get();
        mPanels.push_back(std::move(panel));
    }
}

clt::editor::IEditorPanel* clt::editor::PanelManager::FindByID(const std::string& id) const
{
    auto it = mPanelsById.find(id);
    if (it != mPanelsById.end()) return it->second;
    return nullptr;
}

std::string clt::editor::PanelManager::GetRegisteredID(IEditorPanel* panel) const
{
    auto it = mIdOverrides.find(panel);
    if (it != mIdOverrides.end()) return it->second;
    return panel ? panel->GetID() : std::string();
}

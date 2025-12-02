#pragma once
#include <Core/CCommon.h>
#include <Editor/Services/ImGuiContextService.h>
#include <Editor/UI/PanelManager.h>
#include <Editor/Services/EditorContext.h>

namespace clt
{
	namespace editor
	{
        class CLUTTER_API EditorUIManager 
	    {
        	ImGuiContextService* mImGui{nullptr};
        	EditorContext* mEditorContext{nullptr};
        	
        	bool mDockInitialized{false};
        	
        public:
        	EditorUIManager(ImGuiContextService* imgui, EditorContext* ctx) : mImGui(imgui), mEditorContext(ctx) {};
        	~EditorUIManager() = default;
        	
        	void BeginFrame();
        	void Draw();
        	void EndFrame();
        };
	}
}
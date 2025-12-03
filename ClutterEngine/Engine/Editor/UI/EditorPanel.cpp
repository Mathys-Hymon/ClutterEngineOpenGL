#include "pch.h"
#include "EditorPanel.h"
#include <imgui_internal.h>

bool clt::editor::EditorPanel::Begin()
{
    if (!mIsOpen) return false;
    
    bool* pCloseButton = mIsDocked ? nullptr : &mIsOpen;
    ctx->themes->BindFont(TextType::title);
    bool visible = ImGui::Begin(GetName(), pCloseButton, GetPanelFlags());
    ctx->themes->BindFont(TextType::classic);
    
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    mIsDocked = (window->DockNode != nullptr && window->DockNode->HostWindow != nullptr);

    if (mIsOpen) mWasOpen = mIsOpen;
    
    return visible;
}

void clt::editor::EditorPanel::End()
{
    if (!mWasOpen) return;
    mWasOpen = mIsOpen;
    ImGui::End();
}

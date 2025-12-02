#include "pch.h"
#include  "EditorUIManager.h"
#include "imgui.h"

#include "imgui_internal.h"

void clt::editor::EditorUIManager::BeginFrame()
{
    if (mImGui) mImGui->NewFrame();
}

void clt::editor::EditorUIManager::Draw()
{
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    
    windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                   ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    
    ImGui::Begin("DockSpace_Main", nullptr, windowFlags);
    ImGui::PopStyleVar(2);
    
    ImGuiID dockSpaceID = ImGui::GetID("DockSpace_Main");
    ImGui::DockSpace(dockSpaceID, ImVec2(0.f, 0.f), ImGuiDockNodeFlags_PassthruCentralNode);
    
    if (!mDockInitialized)
    {
        mDockInitialized = true;
        
        ImGui::DockBuilderRemoveNode(dockSpaceID);
        ImGui::DockBuilderAddNode(dockSpaceID, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockSpaceID, viewport->Size);
        
        ImGuiID dock_main_id   = dockSpaceID;
        ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.25f, nullptr, &dock_main_id);
        ImGuiID dock_toolbar   = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.07f, nullptr, &dock_main_id);
        ImGuiID dock_id_left   = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, nullptr, &dock_main_id);
        ImGuiID dock_id_right  = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);
        
        ImGui::DockBuilderDockWindow("ViewportToolBar", dock_toolbar);
        ImGui::DockBuilderDockWindow("Viewport", dock_main_id);
        ImGui::DockBuilderDockWindow("Outliner", dock_id_left);
        ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
        ImGui::DockBuilderDockWindow("Content Browser", dock_id_bottom);
        ImGui::DockBuilderDockWindow("Console", dock_id_bottom);
        
        ImGui::DockBuilderGetNode(dock_toolbar)->LocalFlags |= ImGuiDockNodeFlags_NoResize;
        ImGui::DockBuilderGetNode(dock_toolbar)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
        ImGui::DockBuilderFinish(dockSpaceID);
    }
    
    /* Example Menu Bar
     * TODO : Open, Edit & Save Projects
     */
    
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File")) { ImGui::EndMenu(); }
        if (ImGui::BeginMenu("Edit")) { ImGui::EndMenu(); }
        ImGui::EndMenuBar();
    }
    
    ImGui::End();
    
    for (const auto& ptr : mEditorContext->panels->GetPanels())
    {
        IEditorPanel* panel = ptr.get();
        if (!panel) continue;
        
        ImGui::Begin(panel->GetName(), nullptr, panel->GetWindowFlags());
        panel->Draw();
        ImGui::End();
    }
}

void clt::editor::EditorUIManager::EndFrame()
{
    if (mImGui) mImGui->Render();
}

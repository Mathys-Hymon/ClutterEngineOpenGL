#include "pch.h"
#include "ThemePanel.h"
#include "imgui.h"

clt::editor::ThemePanel::ThemePanel(EditorContext* context) : ctx(context)
{
    SetOpen(false);
}

const char* clt::editor::ThemePanel::GetName() const
{
    return "Editor Appearance";
}

void clt::editor::ThemePanel::Draw()
{
    if (!ctx || !ctx->themes)
    {
        ImGui::Text("Error: ThemeManager not initialized in Context.");
        return;
    }
    
    ImGui::Text("Editor Theme Settings:");
    ImGui::Separator();
    
    if (ImGui::Button("Save Theme"))
    {
        ctx->themes->SaveTheme();
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset to Default"))
    {
        ctx->themes->ApplyDefaultTheme();
    }
    ImGui::Separator();
    ImGui::Spacing();
    
    ImGuiStyle& style = ImGui::GetStyle();
    
    ImGui::BeginChild("ColorsList");
    for (int i = 0; i < ImGuiCol_COUNT; i++)
    {
        const char* name = ImGui::GetStyleColorName(i);
        ImGui::PushID(i);
        ImGui::ColorEdit4(name, (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview);
        ImGui::PopID();
    }
    ImGui::EndChild();
}

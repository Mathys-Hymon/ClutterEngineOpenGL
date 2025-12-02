#include "pch.h"
#include "ThemeManager.h"

#include <json/json.hpp>

#include "imgui.h"
#include "Core/JsonUtility.h"
#include <cstdlib>

clt::editor::ThemeManager::ThemeManager()
{
    const char* appDataPath = std::getenv("APPDATA");
    std::filesystem::path rootPath;
    
    if (appDataPath)
    {
        rootPath = appDataPath;
    }
    else
    {
        const char* drive = std::getenv("SystemDrive");
        rootPath = drive ? drive : "C:\\Program Files";
    }
    
    std::filesystem::path fullPath = rootPath / std::filesystem::path("ClutterEngine/Editor/EditorAppearance.CltSettings");
    
    mFilePath = fullPath.generic_string();
    CLUTTER_LOG("[ThemeManager] Config path set to :" + mFilePath);
    
    if (!LoadTheme()) ApplyDefaultTheme();
}

void clt::editor::ThemeManager::ApplyDefaultTheme()
{
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        // Base palette
        ImVec4 bgColor(0.157f, 0.149f, 0.176f, 1.0f);
        ImVec4 textColor(0.682f, 0.651f, 0.647f, 1.0f);

        colors[ImGuiCol_WindowBg] = bgColor;
        colors[ImGuiCol_ChildBg] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
        colors[ImGuiCol_PopupBg] = bgColor;
        colors[ImGuiCol_Text] = textColor;
        colors[ImGuiCol_TextDisabled] = ImVec4(textColor.x * 0.7f, textColor.y * 0.7f, textColor.z * 0.7f, 1.0f);
        colors[ImGuiCol_Header] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);
        colors[ImGuiCol_HeaderActive] = ImVec4(bgColor.x * 0.8f, bgColor.y * 0.8f, bgColor.z * 0.8f, 1.0f);
        colors[ImGuiCol_Button] = ImVec4(bgColor.x * 1.1f, bgColor.y * 1.1f, bgColor.z * 1.1f, 1.0f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(bgColor.x * 1.3f, bgColor.y * 1.3f, bgColor.z * 1.3f, 1.0f);
        colors[ImGuiCol_ButtonActive] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
        colors[ImGuiCol_Border] = ImVec4(bgColor.x * 0.6f, bgColor.y * 0.6f, bgColor.z * 0.6f, 1.0f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(bgColor.x * 1.1f, bgColor.y * 1.1f, bgColor.z * 1.1f, 1.0f);
        colors[ImGuiCol_Tab] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
        colors[ImGuiCol_TabHovered] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
        colors[ImGuiCol_TabActive] = ImVec4(bgColor.x * 1.1f, bgColor.y * 1.1f, bgColor.z * 1.1f, 1.0f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(bgColor.x * 0.8f, bgColor.y * 0.8f, bgColor.z * 0.8f, 1.0f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(bgColor.x * 0.9f, bgColor.y * 0.9f, bgColor.z * 0.9f, 1.0f);
        colors[ImGuiCol_CheckMark] = textColor;
        colors[ImGuiCol_SliderGrab] = ImVec4(bgColor.x * 1.2f, bgColor.y * 1.2f, bgColor.z * 1.2f, 1.0f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(bgColor.x * 1.4f, bgColor.y * 1.4f, bgColor.z * 1.4f, 1.0f);
}

void clt::editor::ThemeManager::SaveTheme()
{
    nlohmann::json root;
    ImGuiStyle& stype = ImGui::GetStyle();
    
    for (int i = 0; i < ImGuiCol_COUNT; i++)
    {
        const ImVec4& col = stype.Colors[i];
        root["colors"][i] = { col.x, col.y, col.z, col.w};
        
        std::filesystem::path path(mFilePath);
        if (path.has_parent_path())
        {
            try
            {
                std::filesystem::create_directories(path.parent_path());
            } catch (const std::exception& e)
            {
                CLUTTER_ERROR("[ThemeManager::SaveTheme] Failed to create parent directory");
                return;
            }
        }
        
        if (JsonUtility::SaveToFile(mFilePath, root))
        {
            CLUTTER_INFO("[ThemeManager::SaveTheme] Theme saved successfully to " + mFilePath);
        }
    }
}

bool clt::editor::ThemeManager::LoadTheme()
{
    nlohmann::json root;
    
    if (!std::filesystem::exists(mFilePath))
    {
        CLUTTER_INFO("[ThemeManager::LoadTheme] No theme file found at " + mFilePath + ", applying default.");
        return false;
    }
    
    if (!JsonUtility::LoadFromFile(mFilePath, root))
    {
        return false;
    }
    
    ImGuiStyle& style = ImGui::GetStyle();
    
    if (root.contains("colors"))
    {
        for (int i = 0; i < ImGuiCol_COUNT; i++)
        {
            if (i < root["colors"].size())
            {
                auto colorArr = root["colors"][i];
                if (colorArr.size() == 4)
                {
                    style.Colors[i] = ImVec4(
                        colorArr[0].get<float>(),
                        colorArr[1].get<float>(),
                        colorArr[2].get<float>(),
                        colorArr[3].get<float>()
                    );
                }
            }
        }
        
        CLUTTER_INFO("[ThemeManager::LoadTheme] Theme loaded.");
        return true;
    }
}

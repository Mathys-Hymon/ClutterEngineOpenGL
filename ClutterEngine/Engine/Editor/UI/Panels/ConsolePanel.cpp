#include "pch.h"
#include "ConsolePanel.h"
#include "imgui.h"

clt::editor::ConsolePanel::ConsolePanel(EditorContext* context) : EditorPanel(context)
{
}

const char* clt::editor::ConsolePanel::GetName() const
{
    return "Console";
}

clt::editor::DockPosition clt::editor::ConsolePanel::GetDockingPos() const
{
    return DockPosition::bottom;
}

void clt::editor::ConsolePanel::Draw()
{
    const ImVec4 infoColor(0.4f, 1.0f, 0.4f, 1.0f);
    const ImVec4 logColor(1.0f, 1.0f, 1.0f, 1.0f);
    const ImVec4 warningColor(1.0f, 1.0f, 0.2f, 1.0f);
    const ImVec4 errorColor(1.0f, 0.2f, 0.2f, 1.0f);
    
    auto drawFilterButton = [](const char* label, bool& active, ImVec4 color)
        {
            ImVec4 baseColor = ImVec4(0.133f, 0.127f, 0.150f, 1.0f);
            if (active) baseColor = ImVec4(0.110f, 0.104f, 0.123f, 1.0f);

            ImGui::PushStyleColor(ImGuiCol_Button, baseColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(baseColor.x + 0.1f, baseColor.y + 0.1f, baseColor.z + 0.1f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, baseColor);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12, 6));

            bool pushedColor = false;
            if (active)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, color);
                pushedColor = true;
            }

            if (ImGui::Button(label))
                active = !active;

            if (pushedColor)
                ImGui::PopStyleColor();

            ImGui::PopStyleVar(2);
            ImGui::PopStyleColor(3);
        };
    
    drawFilterButton("INFO", mShowInfo, infoColor);    ImGui::SameLine();
    drawFilterButton("LOG", mShowLog, logColor);     ImGui::SameLine();
    drawFilterButton("WARNING", mShowWarning, warningColor); ImGui::SameLine();
    drawFilterButton("ERROR", mShowError, errorColor);
    
    ImGui::BeginChild("LogRegion", ImVec2(0, -30), true);

    bool noFilterActive = !mShowInfo && !mShowLog && !mShowWarning && !mShowError;

    for (const auto& entry : CLog::GetEntries())
    {
        bool show = noFilterActive;
        if (!show)
        {
            switch (entry.level)
            {
            case CLog::LogLevel::INFO:    show = mShowInfo;    break;
            case CLog::LogLevel::LOG:     show = mShowLog;     break;
            case CLog::LogLevel::WARNING: show = mShowWarning; break;
            case CLog::LogLevel::CERROR:  show = mShowError;   break;
            default:                      show = true;        break;
            }
        }

        if (show)
        {
            ImVec4 color;
            switch (entry.level)
            {
            case CLog::LogLevel::INFO:    color = infoColor;    break;
            case CLog::LogLevel::LOG:     color = logColor;     break;
            case CLog::LogLevel::WARNING: color = warningColor; break;
            case CLog::LogLevel::CERROR:  color = errorColor;   break;
            default:                      color = logColor;     break;
            }

            ImGui::PushStyleColor(ImGuiCol_Text, color);
            std::string fullMessage = entry.timeStamp + " | " + entry.message;
            ImGui::TextWrapped("%s", fullMessage.c_str());
            ImGui::PopStyleColor();
        }
    }

    ImGui::EndChild();

    ImGui::SetCursorPosY(ImGui::GetWindowContentRegionMax().y - ImGui::GetFrameHeight());
    ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x - ImGui::CalcTextSize("Clear").x - ImGui::GetStyle().FramePadding.x * 2);

    if (ImGui::Button("Clear"))
        CLog::ClearEntries();
}

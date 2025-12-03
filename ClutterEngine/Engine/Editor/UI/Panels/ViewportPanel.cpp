#include "pch.h"
#include "ViewportPanel.h"
#include <Core/Assets/Assets.h>
#include "imgui.h"
#include "Graphics/FrameBuffer/FrameBuffer.h"

clt::editor::ViewportPanel::ViewportPanel(EditorContext* context) : EditorPanel(context)
{
    moveIconID = Assets::Get()
        .LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/moveGizmoIcon.png", "moveIcon", TextureFilter::LINEAR, true, false)
        .get()->GetID();

    moveIconActiveID = Assets::Get()
        .LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/moveGizmoIconActive.png", "moveIconActive", TextureFilter::LINEAR, true, false)
        .get()->GetID();

    rotateIconID = Assets::Get()
        .LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/RotateGizmoIcon.png", "rotateIcon", TextureFilter::LINEAR, true, false)
        .get()->GetID();

    rotateIconActiveID = Assets::Get()
        .LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/RotateGizmoIconActive.png", "rotateIconActive", TextureFilter::LINEAR, true, false)
        .get()->GetID();

    scaleIconID = Assets::Get()
        .LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/ScaleGizmoIcon.png", "scaleIcon", TextureFilter::LINEAR, true, false)
        .get()->GetID();

    scaleIconActiveID = Assets::Get()
        .LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/ScaleGizmoIconActive.png", "scaleIconActive", TextureFilter::LINEAR, true, false)
        .get()->GetID();

    mActorGizmo = new Gizmo();
}

const char* clt::editor::ViewportPanel::GetName() const
{
    return "Viewport";
}

clt::editor::DockPosition clt::editor::ViewportPanel::GetDockingPos() const
{
    return DockPosition::center();
}

void clt::editor::ViewportPanel::Draw()
{

    if (ImGui::BeginTabBar("ViewportTabs"))
    {
        if (ImGui::BeginTabItem("Scene"))
        {
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Game"))
        {
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

        const bool hovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
        
       // mApp->mEditorCam->GetComponentOfType<EditorController>()->SetCanMove(hovered);

        const ImVec2 availSize = ImGui::GetContentRegionAvail();
        float targetRatio = 16.0f / 9.0f;

        ImVec2 renderSize = availSize;
        float availRatio = (availSize.y == 0.0f) ? targetRatio : (availSize.x / availSize.y);
        if (availRatio > targetRatio)
        {
            renderSize.x = availSize.y * targetRatio;
            renderSize.y = availSize.y;
        }
        else
        {
            renderSize.x = availSize.x;
            renderSize.y = (targetRatio == 0.0f) ? availSize.y : (availSize.x / targetRatio);
        }

        ImVec2 cursorPos = ImGui::GetCursorPos();
        cursorPos.x += (availSize.x - renderSize.x) * 0.5f;
        ImGui::SetCursorPosX(cursorPos.x);

        if (!ctx->sceneFrameBuffer) return;
        uint32_t texID = ctx->sceneFrameBuffer->GetColorAttachment();
        ImGui::Image((void*)(intptr_t)texID, renderSize, ImVec2(0, 1), ImVec2(1, 0));

        ImVec2 viewportStart = ImGui::GetItemRectMin();
        ImVec2 viewportEnd = ImGui::GetItemRectMax();
        (void)viewportEnd;

        const auto buttonPos = ImVec2(viewportStart.x + 10, viewportStart.y + 10);
        ImGui::SetCursorScreenPos(buttonPos);

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 4));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.4f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.3f, 0.3f, 0.8f));

        static bool is2D = false;
        bool was2D = is2D;

        ImVec4 activeColor = ImVec4(0.2f, 0.6f, 1.0f, 1.0f);
        ImVec4 activeOverColor = activeColor;
        ImVec4 activeActivationColor = activeColor;

        if (is2D)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, activeColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, activeOverColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeActivationColor);
        }

        if (ImGui::Button("2D"))  is2D = !is2D;
    
        if (was2D) ImGui::PopStyleColor(3);

        static bool moveActive = true;
        static bool rotateActive = false;
        static bool scaleActive = false;

        ImGui::SameLine();
        if (ImGui::ImageButton("Translate", moveActive ? moveIconActiveID : moveIconID, { 16,16 }))
        {
            mActorGizmo->SetMode(GizmoMode::Translate); 
            moveActive = true;
            rotateActive = false;
            scaleActive = false;
        }
        ImGui::SameLine();
        if (ImGui::ImageButton("Rotate", rotateActive ? rotateIconActiveID : rotateIconID, { 16,16 }))
        {
            mActorGizmo->SetMode(GizmoMode::Rotate);
            moveActive = false;
            rotateActive = true;
            scaleActive = false;
        }
        ImGui::SameLine();
        if (ImGui::ImageButton("Scale", scaleActive ? scaleIconActiveID : scaleIconID, { 16,16 }))
        {
            mActorGizmo->SetMode(GizmoMode::Scale);
            moveActive = false;
            rotateActive = false;
            scaleActive = true;
        }

        ImGui::PopStyleColor(3);
        ImGui::PopStyleVar(2);

}

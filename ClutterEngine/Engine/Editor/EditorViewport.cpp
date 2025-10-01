#include <pch.h>
#include "EditorViewport.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "ImGuizmo.h"
#include "ImGuiLayer.h"
#include <Application/EditorApplication.h>
#include <Core/ActorComponent/Components/Movements/EditorController.h>

using namespace clt;

EditorViewport::EditorViewport(ImGuiLayer* owner, FrameBuffer* sceneFramebuffer) : mOwner(owner), mSceneFramebuffer(sceneFramebuffer), mApp(mOwner->GetOwner())
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

void EditorViewport::Draw(Actor* focusedActor)
{
    ImGui::Begin("Viewport");

    static int currentTab = 0;
    if (ImGui::BeginTabBar("ViewportTabs"))
    {
        if (ImGui::BeginTabItem("Scene"))
        {
            currentTab = 0;
            if (mOwner) mApp->SetCamera(false);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Game"))
        {
            currentTab = 1;
            if (mOwner) mApp->SetCamera(true);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    bool hovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
    if (mOwner && mApp->mEditorCam)
        mApp->mEditorCam->GetComponentOfType<EditorController>()->SetCanMove(hovered);

    if (mSceneFramebuffer)
    {
        if (focusedActor && mActorGizmo->GetTransform() != focusedActor->GetActorTransform())
        {
            mActorGizmo->SetTransform(focusedActor->GetActorTransform());
        }

        ImVec2 availSize = ImGui::GetContentRegionAvail();
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

        uint32_t texID = mSceneFramebuffer->GetColorAttachment();
        ImGui::Image((void*)(intptr_t)texID, renderSize, ImVec2(0, 1), ImVec2(1, 0));

        ImVec2 viewportStart = ImGui::GetItemRectMin();
        ImVec2 viewportEnd = ImGui::GetItemRectMax();
        (void)viewportEnd;

        if (focusedActor) mActorGizmo->Draw({ viewportStart.x, viewportStart.y }, { viewportEnd.x, viewportEnd.y });
        DrawGizmoCamera({viewportStart.x, viewportStart.y}, {viewportEnd.x, viewportEnd.y});

        ImVec2 buttonPos = ImVec2(viewportStart.x + 10, viewportStart.y + 10);
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

        if (is2D && !was2D && mApp && mApp->mEditorCam)
        {
            mApp->mEditorCam->GetComponentOfType<CameraComponent>()->SetProjectionMode(ProjectionMode::Orthographic);
            mApp->mEditorCam->SetActorRotation(0);
        }
        else if (!is2D && was2D && mApp && mApp->mEditorCam)
        {
            mApp->mEditorCam->GetComponentOfType<CameraComponent>()->SetProjectionMode(ProjectionMode::Perspective);
        }

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

    if (focusedActor && mActorGizmo->GetTransform() != focusedActor->GetActorTransform())
    {
        focusedActor->SetActorTransform(mActorGizmo->GetTransform());
    }

    ImGui::End();
}

void EditorViewport::DrawGizmoCamera(const Vector2& startViewport, const Vector2& endViewport)
{
#ifdef EDITOR

    if (!mOwner || !mApp) return;

    CameraComponent* cam = mOwner->GetOwner()->mEditorCam->GetComponentOfType<CameraComponent>();
    if (!cam || cam != CameraComponent::GetActiveCamera()) return;

    bool is2D = cam->GetProjectionMode() == ProjectionMode::Orthographic;

    ImVec2 viewportMin = ImGui::GetWindowContentRegionMin();
    ImVec2 viewportMax = ImGui::GetWindowContentRegionMax();
    ImVec2 windowPos = ImGui::GetWindowPos();

    float gizmoSize = 80.0f;

    ImVec2 gizmoPos;
    gizmoPos.x = startViewport.x + 5.0f;
    gizmoPos.y = endViewport.y - gizmoSize - 5.0f;


    ImDrawList* drawList = ImGui::GetForegroundDrawList();
    drawList->PushClipRect({startViewport.x, startViewport.y}, { endViewport.x, endViewport.y }, true);

    ImVec2 center(gizmoPos.x + gizmoSize * 0.5f, gizmoPos.y + gizmoSize * 0.5f);
    float arrowLength = gizmoSize * 0.4f;

    Vector3 forward = Vector3::Forward;
    Vector3 right = Vector3::Right;
    Vector3 up = Vector3::Up;

    auto ProjectAxis = [&](Vector3 axis) -> ImVec2
        {
            float x = Vector3::Dot(axis, cam->GetWorldTransform().Right());
            float y = Vector3::Dot(axis, cam->GetWorldTransform().Up());
            return ImVec2(center.x + x * arrowLength,
                center.y - y * arrowLength);
        };

    float textOffset = 0.4f;

    ImVec2 yEnd = ProjectAxis(up);
    ImVec2 xEnd = ProjectAxis(right);
    ImVec2 zEnd = ProjectAxis(forward);

    ImVec2 xEndOffset = ProjectAxis(right + right * textOffset);
    ImVec2 yEndOffset = ProjectAxis(up + up * textOffset);
    ImVec2 zEndOffset = ProjectAxis(forward + forward * textOffset);

    drawList->AddLine(center, xEnd, IM_COL32(255, 0, 0, 255), 2.0f);
    drawList->AddLine(center, yEnd, IM_COL32(0, 255, 0, 255), 2.0f);
    if (!is2D) drawList->AddLine(center, zEnd, IM_COL32(0, 0, 255, 255), 2.0f);

    float sphereRadius = 5.0f;
    drawList->AddCircleFilled(xEnd, sphereRadius, IM_COL32(255, 0, 0, 255));
    drawList->AddCircleFilled(yEnd, sphereRadius, IM_COL32(0, 255, 0, 255));
    if (!is2D) drawList->AddCircleFilled(zEnd, sphereRadius, IM_COL32(0, 0, 255, 255));

    auto DrawCenteredText = [&](ImVec2 pos, const char* text, ImU32 color)
        {
            ImVec2 textSize = ImGui::CalcTextSize(text);
            ImVec2 textPos(pos.x - textSize.x * 0.5f, pos.y - textSize.y * 0.5f);
            drawList->AddText(textPos, color, text);
        };

    ImVec2 mousePos = ImGui::GetIO().MousePos;
    float clickRadius = 10.0f;

    auto IsHovered = [&](ImVec2 pos) -> bool
        {
            if (!is2D)
            {
                ImVec2 delta = ImVec2(mousePos.x - pos.x, mousePos.y - pos.y);
                return (delta.x * delta.x + delta.y * delta.y) <= clickRadius * clickRadius;
            }
            else return false;
        };

    ImU32 xColor = IsHovered(xEndOffset) ? IM_COL32(255, 150, 150, 255) : IM_COL32(255, 0, 0, 255);
    ImU32 yColor = IsHovered(yEndOffset) ? IM_COL32(150, 255, 150, 255) : IM_COL32(0, 255, 0, 255);
    ImU32 zColor = IsHovered(zEndOffset) ? IM_COL32(150, 150, 255, 255) : IM_COL32(0, 0, 255, 255);

    DrawCenteredText(xEndOffset, "X", xColor);
    DrawCenteredText(yEndOffset, "Y", yColor);
    if (!is2D) DrawCenteredText(zEndOffset, "Z", zColor);

    if (ImGui::IsMouseClicked(0) && !is2D)
    {
        if (IsHovered(xEndOffset))
            mApp->mEditorCam->SetActorRotation({ 0,90,0 });
        else if (IsHovered(yEndOffset))
            mApp->mEditorCam->SetActorRotation({ 90,0,0 });
        else if (IsHovered(zEndOffset))
            mApp->mEditorCam->SetActorRotation({ 0,0,0 });

        mApp->mEditorCam->GetComponentOfType<EditorController>()->SyncRotation();
    }
#endif
}
#include "pch.h"
#include <filesystem>
#include <Core/Assets/Assets.h>
#include "ContentBrowser.h"
#include <imgui.h>

using namespace clt;

ContentBrowser::ContentBrowser()
{
    mRootFolder.Name = "Content";
    mRootFolder.Path = "Content";
    ScanFolder(mRootFolder.Path);
    mCurrentFolder = &mRootFolder;

    SetFolderIcon(Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/folder.png", "folder Icon", TextureFilter::LINEAR, false, false)->GetID());
    SetAssetIcon(AssetType::Mesh, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/meshFile.png", "mesh Icon", TextureFilter::LINEAR, false, false));
    SetAssetIcon(AssetType::Font, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/fontFile.png", "font Icon", TextureFilter::LINEAR, false, false));
    SetAssetIcon(AssetType::Shader, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/shaderFile.png", "shader Icon", TextureFilter::LINEAR, false, false));
    SetAssetIcon(AssetType::Sound, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/audioFile.png", "audio Icon", TextureFilter::LINEAR, false, false));
    SetAssetIcon(AssetType::Script, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/scriptFile.png", "script Icon", TextureFilter::LINEAR, false, false));
}

void ContentBrowser::ScanFolder(const std::string& root)
{
    mRootFolder.Children.clear();
    mRootFolder.Items.clear();
    ScanFolderRecursive(mRootFolder);
}

void ContentBrowser::ScanFolderRecursive(ContentFolder& folder)
{
    namespace fs = std::filesystem;

    for (auto& p : fs::directory_iterator(folder.Path))
    {
        if (p.is_directory())
        {
            ContentFolder child;
            child.Name = p.path().filename().string();
            child.Path = p.path().string();
            child.Parent = &folder;

            folder.Children.push_back(child);

            ContentFolder& ref = folder.Children.back();
            ScanFolderRecursive(ref);
        }
        else if (p.is_regular_file())
        {
            ContentItem item;
            item.Name = p.path().filename().string();
            item.Path = p.path().string();

            std::string ext = p.path().extension().string();
            if (ext == ".png" || ext == ".jpg") item.Type = AssetType::Texture;
            else if (ext == ".fbx" || ext == ".obj") item.Type = AssetType::Mesh;
            else if (ext == ".ttf") item.Type = AssetType::Font;
            else if (ext == ".wav" || ext == ".mp3" || ext == ".avi") item.Type = AssetType::Sound;
            else if (ext == ".cpp" || ext == ".h") item.Type = AssetType::Script;
            else if (ext == ".frag" || ext == ".tese" || ext == ".vert" || ext == ".tesc") item.Type = AssetType::Shader;
            else item.Type = AssetType::Unknown;

            folder.Items.push_back(item);
        }
    }
}

void ContentBrowser::DrawFolderTree(ContentFolder* folder)
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow |
        ((folder == mCurrentFolder) ? ImGuiTreeNodeFlags_Selected : 0);

    bool node_open = ImGui::TreeNodeEx(folder->Name.c_str(), flags);

    if (ImGui::IsItemClicked(0))
        mCurrentFolder = folder;

    if (node_open)
    {
        for (auto& child : folder->Children)
            DrawFolderTree(&child);
        ImGui::TreePop();
    }
}

void ContentBrowser::Draw()
{
    ImGui::Begin("Content Browser");

    // ---- Partie gauche: hiérarchie ----
    ImGui::BeginChild("Hierarchy", ImVec2(200, 0), true);
    DrawFolderTree(&mRootFolder);
    ImGui::EndChild();

    ImGui::SameLine();

    // ---- Partie droite: contenu du dossier ----
    ImGui::BeginChild("Content", ImVec2(0, 0), true);

    if (!mCurrentFolder) { ImGui::EndChild(); ImGui::End(); return; }

    if (mCurrentFolder != &mRootFolder)
    {
        ImGui::BeginGroup();
        if (mFolderIcon) ImGui::Image(mFolderIcon, ImVec2(64.75f, 51.25f));

        if (ImGui::IsItemClicked(0) && ImGui::IsMouseDoubleClicked(0))
        {
            mCurrentFolder = mCurrentFolder->Parent;
        }

        ImGui::TextWrapped("..");

        ImGui::EndGroup();
        ImGui::SameLine();
    }

    for (auto& child : mCurrentFolder->Children)
    {
        ImGui::BeginGroup();
        if (mFolderIcon) ImGui::Image(mFolderIcon, ImVec2(64.75f, 51.25f));

        if (ImGui::IsItemClicked(0) && ImGui::IsMouseDoubleClicked(0))
        {
            mCurrentFolder = &child;
        }

        ImGui::TextWrapped("%s", child.Name.c_str());

        ImGui::EndGroup();
        ImGui::SameLine();
    }

    for (auto& item : mCurrentFolder->Items)
    {

        ImGui::BeginGroup();
        ImTextureID icon = 0;

        Texture* tex = nullptr;

        switch (item.Type)
        {
        case AssetType::Texture:

            tex = Assets::Get().LoadTexture(item.Path, item.Name, TextureFilter::LINEAR, true, false).get();

            if (tex)
            {
                GLuint texID = tex->GetID();
                icon = (ImTextureID)(intptr_t)texID;
                ImGui::Image(icon, {64, 64});

                ImGui::TextWrapped("%s", item.Name.c_str());
            }
            break;

        default:

            tex = mAssetIcons[item.Type];

            if (tex)
            {
                GLuint texID = tex->GetID();
                icon = (ImTextureID)(intptr_t)texID;

                Vector2 texSize = tex->GetSize();

                ImGui::Image(icon, { texSize.x * 0.25f, texSize.y * 0.25f });

                ImGui::TextWrapped("%s", item.Name.c_str());
            }
            break;
        }
        ImGui::EndGroup();
        ImGui::SameLine();
    }

    ImGui::NewLine();
    ImGui::EndChild();
    ImGui::End();
}

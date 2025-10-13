#include "pch.h"
#include <filesystem>
#include <Core/Assets/Assets.h>
#include <Core/JsonUtility.h>
#include "ContentBrowser.h"
#include <Core/Maths/Color.h>
#ifdef EDITOR
#include <imgui.h>
#endif

using namespace clt;

static Color hoverColor = Color::Olive;

ContentBrowser::ContentBrowser()
{
#ifdef EDITOR

    mRootFolder.Name = "Content";
    mRootFolder.Path = "Content";
    ScanFolder(mRootFolder.Path);
    mCurrentFolder = &mRootFolder;

    hoverColor.a = 0.25;

    mFolderIcon = Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/folder.png", "folder Icon", TextureFilter::LINEAR, false, false)->GetID();

    SetAssetIcon(AssetType::Mesh, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/meshFile.png", "mesh Icon", TextureFilter::LINEAR, false, false));
    SetAssetIcon(AssetType::Font, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/fontFile.png", "font Icon", TextureFilter::LINEAR, false, false));
    SetAssetIcon(AssetType::Shader, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/shaderFile.png", "shader Icon", TextureFilter::LINEAR, false, false));
    SetAssetIcon(AssetType::Sound, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/audioFile.png", "audio Icon", TextureFilter::LINEAR, false, false));
    SetAssetIcon(AssetType::Script, Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/scriptFile.png", "script Icon", TextureFilter::LINEAR, false, false));

    mFolderOpenIcon = Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/folderIconOpened.png", "folder Opened Icon", 
        TextureFilter::LINEAR, false, false)->GetID();
    mFolderClosedIcon = Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/folderIconClosed.png", "folder Closed Icon", 
        TextureFilter::LINEAR, false, false)->GetID();
#endif
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
            else if (ext == ".frag" || ext == ".tese" || ext == ".vert" || ext == ".tesc" || ext == ".CMaterial") item.Type = AssetType::Shader;
            else item.Type = AssetType::Unknown;

            if (item.Type == AssetType::Texture) Assets::Get().LoadTexture(item.Path, item.Name, TextureFilter::LINEAR, true, false);
            folder.Items.push_back(item);
        }
    }
}

void ContentBrowser::DrawFolderTree(ContentFolder* folder)
{
#ifdef EDITOR

    bool isSelected = (folder == mCurrentFolder);

    bool childSelected = false;
    for (auto& child : folder->Children)
    {
        if (FolderHasChild(&child, mCurrentFolder))
        {
            childSelected = true;
            break;
        }
    }

    if (childSelected || isSelected)
        ImGui::SetNextItemOpen(true, ImGuiCond_Always);

    ImGuiTreeNodeFlags flags = (isSelected ? ImGuiTreeNodeFlags_Selected : 0);

    if (folder->Children.empty())
    {
        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

        std::string label = "##" + folder->Name;
        ImGui::TreeNodeEx(label.c_str(), flags);

        ImGui::SameLine();
        if (mFolderClosedIcon) ImGui::Image((isSelected ? mFolderOpenIcon : mFolderClosedIcon), ImVec2(16, 16));
        ImGui::SameLine();
        ImGui::Text("%s", folder->Name.c_str());

        if (ImGui::IsItemClicked(0)) mCurrentFolder = folder;
    }
    else
    {
        flags |= ImGuiTreeNodeFlags_OpenOnArrow;

        std::string label = "##" + folder->Name;
        bool nodeOpen = ImGui::TreeNodeEx(label.c_str(), flags);

        ImGui::SameLine();
        ImTextureID icon = ((nodeOpen || isSelected) ? mFolderOpenIcon : mFolderClosedIcon);
        if (icon) ImGui::Image(icon, ImVec2(16, 16));

        ImGui::SameLine();
        ImGui::Text("%s", folder->Name.c_str());

        if (ImGui::IsItemClicked(0)) mCurrentFolder = folder;

        if (nodeOpen)
        {
            for (auto& child : folder->Children)
                DrawFolderTree(&child);

            ImGui::TreePop();
        }
    }

#endif
}

void ContentBrowser::DrawContentItems()
{
#ifdef EDITOR
    if (!mCurrentFolder) { ImGui::EndChild(); ImGui::End(); return; }

    float cellSize = 74.0f;
    ImVec2 availRegion = ImGui::GetContentRegionAvail();
    float x = 0.0f;

    // --- Return Folder ---

    if (mCurrentFolder != &mRootFolder)
    {
        ImGui::BeginGroup();
        if (mFolderIcon) ImGui::Image(mFolderIcon, ImVec2(64,64));

        if (ImGui::IsItemHovered())
        {
            ImVec2 min = ImGui::GetItemRectMin();
            ImVec2 max = ImGui::GetItemRectMax();

            ImU32 col = ImGui::GetColorU32(ImVec4(hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a));

            ImGui::GetWindowDrawList()->AddRectFilled(min, max, col, 4.0f);
        }

        if (ImGui::IsItemClicked(0) && ImGui::IsMouseDoubleClicked(0))
        {
            mCurrentFolder = mCurrentFolder->Parent;
        }
        ImGui::TextWrapped("..");

        ImGui::EndGroup();
        ImGui::SameLine(0, 10);

        x += 74;
    }

    // Draw all child folder in folder ---

    for (auto& child : mCurrentFolder->Children)
    {
        if (x + cellSize > availRegion.x)
        {
            ImGui::NewLine();
            x = 0.0f;
        }

        ImGui::BeginGroup();

        ImVec2 folderSize(64, 64);

        if (mFolderIcon) ImGui::Image(mFolderIcon, folderSize);

        if (ImGui::IsItemHovered())
        {
            ImVec2 min = ImGui::GetItemRectMin();
            ImVec2 max = ImGui::GetItemRectMax();

            ImU32 col = ImGui::GetColorU32(ImVec4(hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a));

            ImGui::GetWindowDrawList()->AddRectFilled(min, max, col, 4.0f);
        }

        if (ImGui::IsItemClicked(0) && ImGui::IsMouseDoubleClicked(0))
        {
            mCurrentFolder = &child;
        }

        ImVec2 textSize = ImGui::CalcTextSize(child.Name.c_str());
        float textPosX = ImGui::GetCursorPosX() + (folderSize.x - textSize.x) * 0.5f;

        ImGui::SetCursorPosX(textPosX);
        ImGui::TextWrapped("%s", child.Name.c_str());

        ImGui::EndGroup();
        ImGui::SameLine(0, 10);
        x += 74;
    }

    // --- Draw all Items in the folder ---

    for (auto& item : mCurrentFolder->Items)
    {
        if (x + cellSize > availRegion.x)
        {
            ImGui::NewLine();
            x = 0.0f;
        }

        ImGui::BeginGroup();
        ImTextureID icon = 0;

        Texture* tex = nullptr;
        ImVec2 texSize;

        switch (item.Type)
        {
        case AssetType::Texture: // Use texture render for Icon if texture

            tex = Assets::Get().GetTexture(item.Name).get();

            if (tex)
            {
                GLuint texID = tex->GetID();
                icon = (ImTextureID)(intptr_t)texID;

                texSize = ImVec2(64, 64);
                ImGui::Image(icon, texSize);

                if (ImGui::IsItemHovered())
                {
                    ImVec2 min = ImGui::GetItemRectMin();
                    ImVec2 max = ImGui::GetItemRectMax();

                    ImU32 col = ImGui::GetColorU32(ImVec4(hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a));

                    ImGui::GetWindowDrawList()->AddRectFilled(min, max, col, 4.0f);
                }
            }
            break;

        default:

            tex = mAssetIcons[item.Type];

            if (tex)
            {
                GLuint texID = tex->GetID();
                icon = (ImTextureID)(intptr_t)texID;

                texSize = { 64, 64 };

                ImGui::Image(icon, texSize);

                if (ImGui::IsItemHovered())
                {
                    ImVec2 min = ImGui::GetItemRectMin();
                    ImVec2 max = ImGui::GetItemRectMax();

                    ImU32 col = ImGui::GetColorU32(ImVec4(hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a));

                    ImGui::GetWindowDrawList()->AddRectFilled(min, max, col, 4.0f);
                }
            }
            break;
        }

        ImVec2 size = ImGui::CalcTextSize(item.Name.c_str());

        std::string displayName = item.Name;
        if (size.x > texSize.x)
        {
            int chars = item.Name.size();
            while (chars > 0 && ImGui::CalcTextSize(displayName.c_str()).x > texSize.y)
            {
                chars--;
                displayName = item.Name.substr(0, chars) + "..";
            }
        }

        float textPosX = ImGui::GetCursorPosX() + (texSize.x - ImGui::CalcTextSize(displayName.c_str()).x) * 0.5f;
        ImGui::SetCursorPosX(textPosX);
        ImGui::Text("%s", displayName.c_str());

        ImGui::EndGroup();
        ImGui::SameLine(0, 10);
        x += 74;

        if (clt::JsonUtility::EndsWith(item.Name, ".CMaterial"))
        {
            std::string path = mCurrentFolder->Path + item.Name + ".CMaterial";

            //materialGraphEditor->LoadGraphFromFile(path);
        }
    }

#endif
}

bool ContentBrowser::FolderHasChild(ContentFolder* folder, ContentFolder* targetChild)
{
    if (!folder) return false;

    for (ContentFolder& child : folder->Children)
    {
        if (&child == targetChild) return true;

        if (FolderHasChild(&child, targetChild)) return true;
    }

    return false;
}

void ContentBrowser::Draw(ImFont* mEditorFontTitle, ImFont* mEditorFont)
{
#ifdef EDITOR

    static float mHierarchyWidth = 250.0f;

    ImGui::Begin("Content Browser");

    ImGui::PushFont(mEditorFont);

    // ---- Left side : Hierarchy ----

    ImGui::BeginChild("Hierarchy", ImVec2(mHierarchyWidth, 0), true);
    DrawFolderTree(&mRootFolder);
    ImGui::EndChild();

    ImGui::PopFont();
    ImGui::SameLine();

    ImGui::InvisibleButton("Splitter", ImVec2(5.0f, -1.0f));
    if (ImGui::IsItemActive())
    {
        mHierarchyWidth += ImGui::GetIO().MouseDelta.x;
        if (mHierarchyWidth < 150.0f) mHierarchyWidth = 150.0f;   // min width
        if (mHierarchyWidth > 800.0f) mHierarchyWidth = 800.0f;  // max width
    }
    ImGui::SameLine();

    ImGui::BeginChild("Content", ImVec2(0, 0), true);

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::MenuItem("New Folder"))
        {
            std::string folderName = "NewFolder";
            int counter = 1;
            std::filesystem::path newPath = mCurrentFolder->Path + "/" + folderName;

            while (std::filesystem::exists(newPath))
            {
                folderName = "NewFolder_" + std::to_string(counter++);
                newPath = mCurrentFolder->Path + "/" + folderName;
            }

            std::filesystem::create_directory(newPath);
            ScanFolder(mCurrentFolder->Path);
        }

        if (ImGui::MenuItem("Create Material"))
        {
            std::string matName = "NewMaterial";
            int counter = 1;
            std::filesystem::path newMatPath = mCurrentFolder->Path + "/" + (matName + ".CMaterial");

            while (std::filesystem::exists(newMatPath))
            {
                matName = "NewMaterial_" + std::to_string(counter++);
                newMatPath = mCurrentFolder->Path + "/" + (matName + ".CMaterial");
            }

            nlohmann::json matJson;
            clt::JsonUtility::Set(matJson, "nodes", nlohmann::json::array());
            clt::JsonUtility::Set(matJson, "links", nlohmann::json::array());

            if (!clt::JsonUtility::SaveToFile(newMatPath.string(), matJson))
            {
                std::cerr << "Failed to create material file: " << newMatPath << "\n";
            }
            ScanFolder(mCurrentFolder->Path);
        }

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Rename"))
        {
            // to do
        }
        if (ImGui::MenuItem("Delete"))
        {
            // to do
        }
        ImGui::EndPopup();
    }

    // ---- Top Breadcrumb ----
    ContentFolder* folder = mCurrentFolder;
    std::vector<ContentFolder*> hierarchy;

    while (folder) 
    {
        hierarchy.push_back(folder);
        folder = folder->Parent;
    }
    std::reverse(hierarchy.begin(), hierarchy.end());

    for (size_t i = 0; i < hierarchy.size(); i++)
    {
        ContentFolder* f = hierarchy[i];

        if (ImGui::SmallButton(f->Name.c_str())) 
        {
            mCurrentFolder = f;
        }

        if (i < hierarchy.size() - 1)
        {
            ImGui::SameLine(0, 5);
            ImGui::Text(">");
            ImGui::SameLine();
        }
    }

    ImGui::Dummy(ImVec2(0.0f, 2.0f));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 2.0f));

    ImGui::PushFont(mEditorFont);
    DrawContentItems();
    ImGui::PopFont();


    ImGui::NewLine();
    ImGui::EndChild();
    ImGui::End();

#endif
}

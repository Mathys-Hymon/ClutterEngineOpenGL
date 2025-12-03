#include "pch.h"

#include <filesystem>
#include <Core/Assets/Assets.h>
#include <Core/JsonUtility.h>
#include "ContentBrowserPanel.h"

#include "imgui.h"


clt::editor::ContentBrowserPanel::ContentBrowserPanel(EditorContext* context) : EditorPanel(context)
{
    mOpenFolderIcon = Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/folderIconOpened.png", "folder Opened Icon", 
TextureFilter::LINEAR, false, false)->GetID();
    mClosedFolderIcon = Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/folderIconClosed.png", "folder Closed Icon", 
        TextureFilter::LINEAR, false, false)->GetID();
    
    mFolderIcon = Assets::Get().LoadTexture("../ClutterEngine/EngineContent/Resources/Textures/folder.png", "folder Icon", 
        TextureFilter::LINEAR, false, false)->GetID();
    
    mRootFolder.Name = "Content";
    mRootFolder.Path = "Content";
    
    mCurrentFolder = &mRootFolder;
    ScanFolder();
}

bool clt::editor::ContentBrowserPanel::FolderHasChild(ContentFolder* folder, ContentFolder* targetChild)
{
    if (!folder) return false;

    for (ContentFolder& child : folder->Children)
    {
        if (&child == targetChild) return true;

        if (FolderHasChild(&child, targetChild)) return true;
    }

    return false;
}

void clt::editor::ContentBrowserPanel::ScanFolderRecursive(ContentFolder& folder)
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

void clt::editor::ContentBrowserPanel::DrawFolderTree(ContentFolder* folder)
{
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
        if (mClosedFolderIcon) ImGui::Image((isSelected ? mOpenFolderIcon : mClosedFolderIcon), ImVec2(16, 16));
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
        ImTextureID icon = ((nodeOpen || isSelected) ? mOpenFolderIcon : mClosedFolderIcon);
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
}

void clt::editor::ContentBrowserPanel::DrawContentItems()
{
      if (!mCurrentFolder) { ImGui::EndChild(); ImGui::End(); return; }

    float cellSize = 74.0f;
    ImVec2 availRegion = ImGui::GetContentRegionAvail();
    float x = 0.0f;

    // --- Return Folder ---

    Color hoverColor = ctx->themes->GetThemeData(ImGuiCol_ButtonHovered);
    hoverColor.a = 0.3f;
    
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

            tex = ctx->themes->GetAssetIcon(item.Type);

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
}

void clt::editor::ContentBrowserPanel::ScanFolder()
{
    mRootFolder.Children.clear();
    mRootFolder.Items.clear();
    ScanFolderRecursive(*mCurrentFolder);
}

const char* clt::editor::ContentBrowserPanel::GetName() const
{
    return "Content Browser";
}

void clt::editor::ContentBrowserPanel::Draw()
{
    static float mHierarchyWidth = 250.0f;
    
    ImGui::BeginChild("Hierarchy", ImVec2(mHierarchyWidth, 0), true);
    DrawFolderTree(&mRootFolder);
    ImGui::EndChild();
    
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

     DrawContentItems();

     ImGui::NewLine();
     ImGui::EndChild();
}

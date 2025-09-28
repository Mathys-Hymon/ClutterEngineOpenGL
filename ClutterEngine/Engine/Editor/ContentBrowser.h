#pragma once
#include <Core/CCommon.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <Core/Assets/AssetsType/Texture.h>

namespace ImGui {
    typedef unsigned long long ImTextureID;
}

struct ImFont;

namespace clt
{
    enum class CLUTTER_API AssetType { Texture, Mesh, Font, Sound, Shader, Script, Unknown };

    struct ContentItem
    {
        std::string Name;
        std::string Path;
        AssetType Type;
    };

    struct ContentFolder
    {
        std::string Name;
        std::string Path;
        ContentFolder* Parent = nullptr;
        std::vector<ContentFolder> Children;
        std::vector<ContentItem> Items;
    };

    class CLUTTER_API ContentBrowser
    {
        ContentFolder mRootFolder;
        ContentFolder* mCurrentFolder;

        ImGui::ImTextureID mFolderIcon;
        std::unordered_map<AssetType, Texture*> mAssetIcons;

        ImGui::ImTextureID mFolderClosedIcon;
        ImGui::ImTextureID mFolderOpenIcon;

        bool FolderHasChild(ContentFolder* folder, ContentFolder* targetChild);

        void ScanFolderRecursive(ContentFolder& folder);

        void DrawFolderTree(ContentFolder* folder);
        void DrawContentItems();

    public:
        ContentBrowser();
        ~ContentBrowser() = default;

        void ScanFolder(const std::string& root);
        void Draw(ImFont* mEditorFontTitle, ImFont* mEditorFont);

        void SetFolderIcon(ImGui::ImTextureID icon) { mFolderIcon = icon; }
        void SetAssetIcon(AssetType type, std::weak_ptr<Texture> icon) { mAssetIcons[type] = icon.lock().get(); }
    };
}
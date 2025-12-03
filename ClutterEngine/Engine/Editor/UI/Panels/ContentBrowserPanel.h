#pragma once
#include <Core/CCommon.h>
#include <Editor/UI/EditorPanel.h>

namespace clt
{
	namespace editor
	{
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
		
		class CLUTTER_API ContentBrowserPanel : public EditorPanel
		{
			ContentFolder mRootFolder;
			ContentFolder* mCurrentFolder;
			
			ImTextureID mOpenFolderIcon;
			ImTextureID mClosedFolderIcon;
			ImTextureID mFolderIcon;
			
			bool FolderHasChild(ContentFolder* folder, ContentFolder* targetChild);

			void ScanFolderRecursive(ContentFolder& folder);

			void DrawFolderTree(ContentFolder* folder);
			void DrawContentItems();
			void ScanFolder();
			
		public:
			ContentBrowserPanel(EditorContext* context);
			const char* GetName() const override;
			void Draw() override;
		};
	}
}
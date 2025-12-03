#pragma once
#pragma warning(disable: 4996)
#include <unordered_map>
#include <Core/CCommon.h>

#include "imgui.h"

enum ImGuiCol_;
struct ImFont;
namespace clt
{
	class Texture;
	namespace editor
	{
		enum class TextType {classic, title, console};
		
		class CLUTTER_API ThemeManager
		{
			std::string mFilePath;
			
			std::unordered_map<AssetType,Texture*> mAssetIcons;
			std::unordered_map<TextType, ImFont*> mEditorFonts;
			
		public:
			ThemeManager();
			~ThemeManager() = default;
			
			void ApplyDefaultTheme();
			void SaveTheme();
			bool LoadTheme();
			
			void BindFont(TextType type);
			void SetFont(TextType type,const char* fontPath, float fontSize = 15.f);
			
			Color GetThemeData(ImGuiCol_ data);
			void SetAssetIcon(AssetType type, std::weak_ptr<class Texture> icon);
			Texture* GetAssetIcon(AssetType type);
		};
	}
}

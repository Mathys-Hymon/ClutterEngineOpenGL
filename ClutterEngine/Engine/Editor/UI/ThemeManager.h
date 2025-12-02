#pragma once
#pragma warning(disable: 4996)
#include <Core/CCommon.h>

namespace clt
{
	namespace editor
	{
		class CLUTTER_API ThemeManager
		{
			std::string mFilePath;
			
			
			
		public:
			ThemeManager();
			~ThemeManager() = default;
			
			void ApplyDefaultTheme();
			void SaveTheme();
			bool LoadTheme();
		};
	}
}
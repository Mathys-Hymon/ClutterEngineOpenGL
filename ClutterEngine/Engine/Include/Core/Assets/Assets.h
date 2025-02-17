#pragma once
#include <unordered_map>
#include <Core/Assets/AssetsType/Texture.h>

namespace clt
{
	class CLUTTER_API Assets
	{
		static Assets* sInstance;

		std::unordered_map<std::string, Texture*> mTextures;
		Assets() = default;
		~Assets();

	public:
		static Assets& Get();

		void LoadTexture(const std::string& path, const std::string& name);
		Texture* GetTexture(const std::string& name);

		void ClearTextures();
	};
}
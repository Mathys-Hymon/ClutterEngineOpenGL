#pragma once
#include <unordered_map>
#include <Core/Assets/AssetsType/Texture.h>

enum class TextureFilter
{
	NEAREST,
	LINEAR
};

namespace clt
{
	class Renderer;
	class CLUTTER_API Assets
	{
		static Assets* sInstance;

		Renderer* mRenderer;

		std::unordered_map<std::string, Texture*> mTextures;
		Assets() = default;
		~Assets();

		void SetRenderer(Renderer* pRenderer) { mRenderer = pRenderer; };

		friend Renderer;

	public:
		static Assets& Get();

		Texture* LoadTexture(const std::string& path, const std::string& name, TextureFilter pTexFilter = TextureFilter::LINEAR);
		Texture* GetTexture(const std::string& name);

		void ClearTextures();
	};
}
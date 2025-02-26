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
	class RendererGL;
	class CLUTTER_API Assets
	{
		static Assets* sInstance;

		RendererGL* mRenderer;

		std::unordered_map<std::string, Texture*> mTextures;
		Assets() = default;
		~Assets();

		void SetRenderer(RendererGL* pRenderer) { mRenderer = pRenderer; };

		friend RendererGL;

	public:
		static Assets& Get();

		Texture* LoadTexture(const std::string& path, const std::string& name, TextureFilter pTexFilter = TextureFilter::LINEAR);
		Texture* GetTexture(const std::string& name);

		void ClearTextures();
	};
}
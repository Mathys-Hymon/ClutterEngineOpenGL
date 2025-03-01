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

		RendererGL* mRenderer = nullptr;

		std::unordered_map<std::string, Texture*> mTextures;
		Assets() = default;
		~Assets() = default;

		void SetRenderer(RendererGL* pRenderer) { mRenderer = pRenderer; };

		friend RendererGL;

	public:
		static Assets& Get();

		Texture* LoadTexture(const std::string& pPath, const std::string& pName, TextureFilter pTexFilter = TextureFilter::LINEAR);

		std::vector<Texture*> BulkLoadTexture(const std::string& pPath, int pLastIndex, const std::string& pFileName, const std::string& pName, TextureFilter pTexFilter = TextureFilter::LINEAR);

		Texture* GetTexture(const std::string& name);

		std::vector<Texture*> BulkGetTexture(const std::string& name, int pLastIndex);

		void ClearTextures();
	};
}
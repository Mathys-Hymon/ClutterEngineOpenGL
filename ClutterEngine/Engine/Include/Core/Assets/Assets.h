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
	class IRenderer;
	class CLUTTER_API Assets
	{
		static Assets* sInstance;

		IRenderer* mRenderer = nullptr;

		std::unordered_map<std::string, Texture*> mTextures;
		Assets() = default;
		~Assets() = default;

		void LoadTextureGL(TextureFilter pTexFilter, GLuint& textureID, int& width, int& height, int& channels, unsigned char* data);

	public:
		static Assets& Get();

		Texture* LoadTexture(const std::string& pPath, const std::string& pName, TextureFilter pTexFilter = TextureFilter::LINEAR);

		void SetRenderer(IRenderer* pRenderer) { mRenderer = pRenderer; };

		std::vector<Texture*> BulkLoadTexture(const std::string& pPath, int pLastIndex, const std::string& pFileName, const std::string& pName, TextureFilter pTexFilter = TextureFilter::LINEAR);

		Texture* GetTexture(const std::string& name);

		std::vector<Texture*> BulkGetTexture(const std::string& name, int pLastIndex);

		void ClearTextures();
	};
}
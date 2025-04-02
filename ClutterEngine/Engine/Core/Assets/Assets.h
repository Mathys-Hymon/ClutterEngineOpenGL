#pragma once
#include <unordered_map>
#include <Core/Assets/AssetsType/Texture.h>
#include <Core/Assets/AssetsType/Mesh.h>
#include <Core/Assets/AssetsType/Font.h>


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
		std::unordered_map<std::string, Mesh*> mMeshes;
		std::unordered_map<std::string, Font*> mFonts;

		 Assets();
		~Assets() = default;

		void LoadTextureGL(TextureFilter pTexFilter, GLuint& textureID, int& width, int& height, int& channels, unsigned char* data);

		Mesh* LoadMeshFromFile(const std::string& pFile);

	public:
		static Assets& Get();

		Texture* LoadTexture(const std::string& pPath, const std::string& pName, TextureFilter pTexFilter = TextureFilter::LINEAR);

		Mesh* LoadMesh(const std::string& pPath, const std::string& pName, std::vector<Texture*> pTextures = {});

		Mesh* LoadMesh(const std::string& pPath, const std::string& pName, const std::string& pTexture);

		Font* LoadFont(const std::string& pPath, const std::string& pName, GLuint pFontSize = 48);

		void SetRenderer(IRenderer* pRenderer) { mRenderer = pRenderer; };

		std::vector<Texture*> BulkLoadTexture(const std::string& pPath, int pLastIndex, const std::string& pFileName, const std::string& pName, TextureFilter pTexFilter = TextureFilter::LINEAR);

		Texture* GetTexture(const std::string& name);
		Mesh* GetMesh(const std::string& name);
		Font* GetFont(const std::string& name);

		std::vector<Texture*> BulkGetTexture(const std::string& name, int pLastIndex);

		void ClearTextures();
	};
}
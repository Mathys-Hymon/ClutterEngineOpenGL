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

		std::unordered_map<ShaderType, std::unordered_map<std::string, Shader*>> mShaders;

		 Assets();
		~Assets() = default;

		void LoadTextureGL(TextureFilter pTexFilter, GLuint& textureID, int& width, int& height, int& channels, unsigned char* data, bool generateMipMaps = true);

		Mesh* LoadMeshFromFile(const std::string& pFile, bool pTesselate);

		void LoadEngineAssets();

	public:
		static Assets& Get();
		void SetRenderer(IRenderer* pRenderer) 
		{
			mRenderer = pRenderer;  
			LoadEngineAssets();
		}


		Texture* LoadTexture(const std::string& pPath, const std::string& pName, TextureFilter pTexFilter = TextureFilter::LINEAR, bool generateMipMaps = true);
		std::vector<Texture*> BulkLoadTexture(const std::string& pPath, int pLastIndex, const std::string& pFileName, const std::string& pName, TextureFilter pTexFilter = TextureFilter::LINEAR);

		Mesh* LoadMesh(const std::string& pPath, const std::string& pName, std::vector<Texture*> pTextures = {}, bool pTesselate = false);
		Mesh* LoadMesh(const std::string& pPath, const std::string& pName, const std::string& pTexture, bool pTesselate = false);
		Mesh* LoadMesh(const std::string& pPath, const std::string& pName, bool pTesselate);

		Font* LoadFont(const std::string& pPath, const std::string& pName, GLuint pFontSize = 128);

		Shader* LoadShader(const std::string& pPath, const std::string& pName, ShaderType pType);

		Texture* GetTexture(const std::string& pName);
		std::vector<Texture*> BulkGetTexture(const std::string& pName, int pLastIndex);
		Mesh* GetMesh(const std::string& pName, bool pTesselate = false);
		Font* GetFont(const std::string& pName);
		Shader* GetShader(const std::string& pName, ShaderType pType);

		void ClearAssets();
	};
}
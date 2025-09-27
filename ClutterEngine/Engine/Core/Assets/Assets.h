#pragma once
#include <unordered_map>
#include <Core/Assets/AssetsType/Texture.h>
#include <Core/Assets/AssetsType/Mesh.h>
#include <Core/Assets/AssetsType/Font.h>
#include <Core/Assets/AssetsType/Sound.h>


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

		std::unordered_map < std::string, std::shared_ptr<Texture>> mTextures;
		std::unordered_map<std::string, std::shared_ptr<IMaterial>> mMaterials;
		std::unordered_map<std::string, std::shared_ptr<Mesh>> mMeshes;
		std::unordered_map<std::string, std::shared_ptr<Font>> mFonts;
		std::unordered_map<std::string, std::shared_ptr<Sound>> mSounds;

		std::unordered_map<ShaderType, std::unordered_map<std::string,Shader*>> mShaders;

		 Assets();
		~Assets() = default;

		void LoadTextureGL(TextureFilter pTexFilter, GLuint& textureID, int& width, int& height, int& channels, unsigned char* data, bool generateMipMaps = true);

		std::shared_ptr<Mesh> LoadMeshFromFile(const std::string& pFile, bool pTesselate);
		std::shared_ptr<Mesh> LoadMeshFromFile(const std::string& pFile, std::shared_ptr<IMaterial> pMaterial, bool pTesselate);

		void LoadEngineAssets();

	public:

		static Assets& Get();
		void SetRenderer(IRenderer* pRenderer) 
		{
			mRenderer = pRenderer;  
			LoadEngineAssets();
		}

		std::shared_ptr<Texture> LoadTexture(const std::string& pPath, const std::string& pName, TextureFilter pTexFilter = TextureFilter::LINEAR, bool generateMipMaps = true, bool flipVertically = true);
		std::vector<std::weak_ptr<Texture>> BulkLoadTexture(const std::string& pPath, int pLastIndex, const std::string& pFileName, const std::string& pName, TextureFilter pTexFilter = TextureFilter::LINEAR, bool pMipMap = true);

		std::shared_ptr<Mesh> LoadMesh(const std::string& pPath, const std::string& pName, std::vector < std::weak_ptr<Texture>> pTextures = {}, bool pTesselate = false);
		std::shared_ptr<Mesh> LoadMesh(const std::string& pPath, const std::string& pName, const std::string& pTexture, bool pTesselate = false);
		std::shared_ptr<Mesh> LoadMesh(const std::string& pPath, const std::string& pName, bool pTesselate);
		std::shared_ptr<Mesh> LoadMesh(const std::string& pPath, const std::string& pName, std::shared_ptr<IMaterial> pMaterial, bool pTesselate = false);

		std::shared_ptr<Font> LoadFont(const std::string& pPath, const std::string& pName, GLuint pFontSize = 128);

		Shader* LoadShader(const std::string& pPath, ShaderType pType);

		std::shared_ptr<Sound> LoadAudio(const std::string& pPath, const std::string& pName, AudioCategory category, bool isSpatialized = true, bool isStream = false);

		std::shared_ptr<IMaterial> CreateMaterial(const std::string& pName, ShaderProgram* pShaderProgram);
		std::shared_ptr<IMaterial> CreateMaterial(const std::string& pName, std::vector<Shader*> pShaders);

		std::shared_ptr<IMaterial> CreateMaterialInstance(const std::string& pName, std::shared_ptr<IMaterial> pParent);

		std::shared_ptr<Texture> GetTexture(const std::string& pName);
		std::shared_ptr<IMaterial> GetMaterial(const std::string& pName);
		std::vector< std::shared_ptr<Texture>> BulkGetTexture(const std::string& pName, int pLastIndex);
		std::shared_ptr<Mesh> GetMesh(const std::string& pName, bool pTesselate = false);
		std::shared_ptr<Font> GetFont(const std::string& pName);
		std::shared_ptr<Sound> GetAudio(const std::string& pName);

		Shader* GetShader(const std::string& pName, ShaderType pType);

		void ClearAssets();
	};
}
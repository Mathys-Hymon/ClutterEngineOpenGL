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
	/**
  * @brief Interface for renderer classes.
  */
	class IRenderer;

	/**
  * @brief Asset management class for textures, meshes, fonts, and shaders.
  * 
  * Handles loading, retrieval, and clearing of engine assets.
  */
	class CLUTTER_API Assets
	{
		static Assets* sInstance; ///< Singleton instance pointer.

		IRenderer* mRenderer = nullptr; ///< Pointer to the renderer.

		std::unordered_map<std::string, Texture*> mTextures; ///< Loaded textures mapped by name.
		std::unordered_map<std::string, Mesh*> mMeshes;      ///< Loaded meshes mapped by name.
		std::unordered_map<std::string, Font*> mFonts;       ///< Loaded fonts mapped by name.

		std::unordered_map<ShaderType, std::unordered_map<std::string, Shader*>> mShaders; ///< Loaded shaders mapped by type and name.

		/**
   * @brief Private constructor for singleton pattern.
   */
		Assets();

		/**
   * @brief Default destructor.
   */
		~Assets() = default;

		/**
   * @brief Loads a texture into OpenGL.
   * @param pTexFilter Texture filtering mode.
   * @param textureID Reference to OpenGL texture ID.
   * @param width Reference to texture width.
   * @param height Reference to texture height.
   * @param channels Reference to number of color channels.
   * @param data Pointer to texture data.
   * @param generateMipMaps Whether to generate mipmaps.
   */
		void LoadTextureGL(TextureFilter pTexFilter, GLuint& textureID, int& width, int& height, int& channels, unsigned char* data, bool generateMipMaps = true);

		/**
   * @brief Loads a mesh from file.
   * @param pFile Path to mesh file.
   * @param pTesselate Whether to tesselate the mesh.
   * @return Pointer to loaded Mesh.
   */
		Mesh* LoadMeshFromFile(const std::string& pFile, bool pTesselate);

		/**
   * @brief Loads a mesh from file with a specific shader.
   * @param pFile Path to mesh file.
   * @param pShader Shader program to use.
   * @param pTesselate Whether to tesselate the mesh.
   * @return Pointer to loaded Mesh.
   */
		Mesh* LoadMeshFromFile(const std::string& pFile, ShaderProgram* pShader, bool pTesselate);

		/**
   * @brief Loads engine-specific assets.
   */
		void LoadEngineAssets();

	public:
		/**
   * @brief Gets the singleton instance of Assets.
   * @return Reference to Assets instance.
   */
		static Assets& Get();

		/**
   * @brief Sets the renderer and loads engine assets.
   * @param pRenderer Pointer to renderer.
   */
		void SetRenderer(IRenderer* pRenderer) 
		{
			mRenderer = pRenderer;  
			LoadEngineAssets();
		}

		/**
   * @brief Loads a texture from file.
   * @param pPath Path to texture file.
   * @param pName Name to assign to the texture.
   * @param pTexFilter Texture filtering mode.
   * @param generateMipMaps Whether to generate mipmaps.
   * @return Pointer to loaded Texture.
   */
		Texture* LoadTexture(const std::string& pPath, const std::string& pName, TextureFilter pTexFilter = TextureFilter::LINEAR, bool generateMipMaps = true);

		/**
   * @brief Loads multiple textures in bulk.
   * @param pPath Path to texture files.
   * @param pLastIndex Last index for bulk loading.
   * @param pFileName File name pattern.
   * @param pName Name pattern for textures.
   * @param pTexFilter Texture filtering mode.
   * @param pMipMap Whether to generate mipmaps.
   * @return Vector of loaded Texture pointers.
   */
		std::vector<Texture*> BulkLoadTexture(const std::string& pPath, int pLastIndex, const std::string& pFileName, const std::string& pName, TextureFilter pTexFilter = TextureFilter::LINEAR, bool pMipMap = true);

		/**
   * @brief Loads a mesh with textures.
   * @param pPath Path to mesh file.
   * @param pName Name to assign to the mesh.
   * @param pTextures Textures to apply to the mesh.
   * @param pTesselate Whether to tesselate the mesh.
   * @return Pointer to loaded Mesh.
   */
		Mesh* LoadMesh(const std::string& pPath, const std::string& pName, std::vector<Texture*> pTextures = {}, bool pTesselate = false);

		/**
   * @brief Loads a mesh with a single texture.
   * @param pPath Path to mesh file.
   * @param pName Name to assign to the mesh.
   * @param pTexture Name of the texture to apply.
   * @param pTesselate Whether to tesselate the mesh.
   * @return Pointer to loaded Mesh.
   */
		Mesh* LoadMesh(const std::string& pPath, const std::string& pName, const std::string& pTexture, bool pTesselate = false);

		/**
   * @brief Loads a mesh.
   * @param pPath Path to mesh file.
   * @param pName Name to assign to the mesh.
   * @param pTesselate Whether to tesselate the mesh.
   * @return Pointer to loaded Mesh.
   */
		Mesh* LoadMesh(const std::string& pPath, const std::string& pName, bool pTesselate);

		/**
   * @brief Loads a mesh with a shader and textures.
   * @param pPath Path to mesh file.
   * @param pName Name to assign to the mesh.
   * @param pShader Shader program to use.
   * @param pTextures Textures to apply to the mesh.
   * @param pTesselate Whether to tesselate the mesh.
   * @return Pointer to loaded Mesh.
   */
		Mesh* LoadMesh(const std::string& pPath, const std::string& pName, ShaderProgram* pShader, std::vector<Texture*> pTextures, bool pTesselate = false);

		/**
   * @brief Loads a mesh with a shader.
   * @param pPath Path to mesh file.
   * @param pName Name to assign to the mesh.
   * @param pShader Shader program to use.
   * @param pTesselate Whether to tesselate the mesh.
   * @return Pointer to loaded Mesh.
   */
		Mesh* LoadMesh(const std::string& pPath, const std::string& pName, ShaderProgram* pShader, bool pTesselate = false);

		/**
   * @brief Loads a font from file.
   * @param pPath Path to font file.
   * @param pName Name to assign to the font.
   * @param pFontSize Size of the font.
   * @return Pointer to loaded Font.
   */
		Font* LoadFont(const std::string& pPath, const std::string& pName, GLuint pFontSize = 128);

		/**
   * @brief Loads a shader from file.
   * @param pPath Path to shader file.
   * @param pType Type of shader.
   * @return Pointer to loaded Shader.
   */
		Shader* LoadShader(const std::string& pPath, ShaderType pType);

		/**
   * @brief Retrieves a loaded texture by name.
   * @param pName Name of the texture.
   * @return Pointer to Texture, or nullptr if not found.
   */
		Texture* GetTexture(const std::string& pName);

		/**
   * @brief Retrieves multiple textures by name pattern.
   * @param pName Name pattern.
   * @param pLastIndex Last index for retrieval.
   * @return Vector of Texture pointers.
   */
		std::vector<Texture*> BulkGetTexture(const std::string& pName, int pLastIndex);

		/**
   * @brief Retrieves a loaded mesh by name.
   * @param pName Name of the mesh.
   * @param pTesselate Whether to retrieve tesselated version.
   * @return Pointer to Mesh, or nullptr if not found.
   */
		Mesh* GetMesh(const std::string& pName, bool pTesselate = false);

		/**
   * @brief Retrieves a loaded font by name.
   * @param pName Name of the font.
   * @return Pointer to Font, or nullptr if not found.
   */
		Font* GetFont(const std::string& pName);

		/**
   * @brief Retrieves a loaded shader by name and type.
   * @param pName Name of the shader.
   * @param pType Type of shader.
   * @return Pointer to Shader, or nullptr if not found.
   */
		Shader* GetShader(const std::string& pName, ShaderType pType);

		/**
   * @brief Clears all loaded assets.
   */
		void ClearAssets();
	};
}
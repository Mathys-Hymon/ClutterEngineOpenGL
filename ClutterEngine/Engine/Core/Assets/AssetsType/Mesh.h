namespace clt
{
	/**
  * @brief Forward declaration of Assets class.
  */
	class Assets;

	/**
  * @brief Structure representing a single vertex.
  */
	struct CLUTTER_API Vertex
	{
		Vector3 position;   ///< Position of the vertex.
		Vector3 normal;     ///< Normal vector at the vertex.
		Vector2 texCoord;   ///< Texture coordinate of the vertex.
	};

	/**
  * @brief Class representing a mesh, including its vertices, textures, and rendering data.
  */
	class CLUTTER_API Mesh
	{
		std::vector<Texture*> mTextures;      ///< List of textures associated with the mesh.
		Vector2 mTextureTiling = { 1,1 };     ///< Tiling factor for the mesh's textures.

		VertexArray* mVAO;                    ///< Vertex Array Object for rendering.

		std::vector<Vertex> mVertices;        ///< List of vertices in the mesh.

		ShaderProgram* mShader;               ///< Shader program used for rendering the mesh.
		bool mTesselate;                      ///< Flag indicating if tessellation is enabled.

		/**
   * @brief Converts the mesh's vertices to a float array.
   * @return Pointer to the float array containing vertex data.
   */
		float* ToVerticeArray();

	public:

		/**
   * @brief Default constructor.
   */
		Mesh() {};

		/**
   * @brief Constructs a mesh from a raw vertex array.
   * @param pVertices Pointer to the vertex data.
   * @param pVerticeCount Number of vertices.
   * @param tesselate Whether tessellation is enabled.
   */
		Mesh(const float* pVertices, u32 pVerticeCount, bool tesselate);

		/**
   * @brief Constructs a mesh from a raw vertex array and a shader.
   * @param pVertices Pointer to the vertex data.
   * @param pVerticeCount Number of vertices.
   * @param pShader Shader program to use.
   * @param isTesselated Whether tessellation is enabled.
   */
		Mesh(const float* pVertices, u32 pVerticeCount, ShaderProgram* pShader, bool isTesselated);

		/**
   * @brief Constructs a mesh from a vector of vertices and a shader.
   * @param pVertices Vector of vertices.
   * @param pShader Shader program to use.
   * @param isTesselated Whether tessellation is enabled.
   */
		Mesh(std::vector<Vertex> pVertices, ShaderProgram* pShader, bool isTesselated);

		/**
   * @brief Constructs a mesh from a vector of vertices.
   * @param pVertices Vector of vertices.
   * @param tesselate Whether tessellation is enabled.
   */
		Mesh(std::vector<Vertex> pVertices, bool tesselate);

		/**
   * @brief Destructor.
   */
		~Mesh() = default;

		/**
   * @brief Unloads the mesh and releases its resources.
   */
		void Unload();

		/**
   * @brief Gets a texture by index.
   * @param pTextureIndex Index of the texture.
   * @return Pointer to the texture.
   */
		Texture* GetTexture(int pTextureIndex);

		/**
   * @brief Checks if the mesh contains a specific texture.
   * @param pTextureIndex Pointer to the texture to check.
   * @return True if the texture exists, false otherwise.
   */
		bool HasTexture(Texture* pTextureIndex)
		{
			for (Texture* tex : mTextures)
			{
				if (tex->GetID() == pTextureIndex->GetID()) return true;
			}
			return false;
		}

		/**
   * @brief Gets the mesh's Vertex Array Object.
   * @return Reference to the VertexArray.
   */
		VertexArray& GetVAO() { return *mVAO; }

		/**
   * @brief Gets the mesh's shader program.
   * @return Reference to the ShaderProgram.
   */
		ShaderProgram& GetShader() { return *mShader; }

		/**
   * @brief Adds a texture to the mesh.
   * @param pTexture Pointer to the texture to add.
   */
		void AddTexture(Texture* pTexture);

		/**
   * @brief Sets a texture at a specific index.
   * @param texture Pointer to the texture.
   * @param index Index to set the texture at.
   */
		void SetTexture(Texture* texture, size_t& index);

		/**
   * @brief Sets a texture by name at a specific index.
   * @param texture Name of the texture.
   * @param index Index to set the texture at.
   */
		void SetTexture(std::string& texture, size_t& index);

		/**
   * @brief Sets the tiling factor for the mesh's textures.
   * @param tiling The tiling factor.
   */
		void SetTextureTiling(Vector2 tiling) { mTextureTiling = tiling; };

		/**
   * @brief Gets the tiling factor for the mesh's textures.
   * @return The tiling factor.
   */
		Vector2 GetTextureTiling() const { return mTextureTiling; };

		/**
   * @brief Checks if tessellation is enabled for the mesh.
   * @return True if tessellation is enabled, false otherwise.
   */
		bool GetTesselated() const { return mTesselate; };

		/**
   * @brief Sets the mesh's Vertex Array Object.
   * @param pVAO Pointer to the VertexArray.
   */
		void SetMesh(VertexArray* pVAO);

		/**
   * @brief Sets the mesh's vertex and index data.
   * @param pVertices Pointer to the vertex data.
   * @param pVerticeCount Number of vertices.
   * @param pIndices Pointer to the index data.
   * @param pIndexCount Number of indices.
   */
		void SetMesh(const float* pVertices, u32 pVerticeCount, const u32* pIndices, u32 pIndexCount);
	};
}
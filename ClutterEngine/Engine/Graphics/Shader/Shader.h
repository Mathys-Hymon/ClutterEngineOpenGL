#pragma once
#include <Core/CCommon.h>
#include <glad/glad.h>

#include <string>

namespace clt
{
	/**
  * @brief Enum representing the type of shader.
  */
	enum class CLUTTER_API ShaderType
	{
		VERTEX,                 /**< Vertex shader */
		FRAGMENT,               /**< Fragment shader */
		TESSELATION_CONTROL,    /**< Tesselation control shader */
		TESSELATION_EVALUATION, /**< Tesselation evaluation shader */
		GEOMETRY                /**< Geometry shader */
	};

	class DebugDraw;

	/**
  * @brief Represents an OpenGL shader object.
  */
	class CLUTTER_API Shader
	{
	protected:
		GLuint mID;              /**< OpenGL shader ID */
		std::string mCode;       /**< Shader source code */
		ShaderType mType;        /**< Type of the shader */

	public:
		/**
   * @brief Default constructor. Initializes shader as a vertex shader with ID 0.
   */
		Shader() : mID(0), mType(ShaderType::VERTEX) {}

		/**
   * @brief Constructs a shader with the given parameters and loads it.
   * @param pID Shader ID.
   * @param pCode Shader source code or file path.
   * @param pShaderType Type of the shader.
   * @param pPath If true, pCode is treated as a file path; otherwise, as source code.
   */
		Shader(int pID, std::string pCode, ShaderType pShaderType, bool pPath = true) : mID(pID),mCode(pCode), mType(pShaderType) { Load(pCode, pShaderType, pPath); }

		/**
   * @brief Destructor. Cleans up the shader object.
   */
		~Shader();

		/**
   * @brief Gets the OpenGL shader ID.
   * @return Shader ID.
   */
		int GetID() { return mID; }

		/**
   * @brief Loads the shader from a file or source code.
   * @param pFileName File name or source code.
   * @param pShaderType Type of the shader.
   * @param pPath If true, pFileName is treated as a file path; otherwise, as source code.
   */
		void Load(std::string pFileName, ShaderType pShaderType, bool pPath = true);

		/**
   * @brief Activates the shader for use.
   */
		void Use();

		/**
   * @brief Gets the shader source code.
   * @return Shader source code.
   */
		const std::string GetCode() const { return mCode; };
	};
}

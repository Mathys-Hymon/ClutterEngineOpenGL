#pragma once
#include <Core/CCommon.h>
#include <Graphics/Shader/Shader.h>
#include <Core/Maths/Vectors/Vector2.h>
#include <Core/Maths/Vectors/Vector4.h>
#include <Core/Maths/Matrix/Matrix4.h>
#include <Core/Maths/Color.h>
#include <Core/Maths/Matrix/Matrix4Row.h>

namespace clt
{
	/**
  * @brief Represents an OpenGL shader program composed of multiple shaders.
  * 
  * Provides methods to compose, use, and set uniform variables for the shader program.
  */
	class CLUTTER_API ShaderProgram
	{
		GLuint mID; ///< OpenGL program ID.
		std::vector<Shader*> mShaders; ///< List of attached shaders.

	public :
		/**
   * @brief Constructs an empty ShaderProgram.
   */
		ShaderProgram();

		/**
   * @brief Destructor. Defaulted.
   */
		~ShaderProgram() = default;

		/**
   * @brief Unloads the shader program and releases resources.
   */
		void Unload();

		/**
   * @brief Composes the shader program from the given shaders.
   * @param shaders Vector of pointers to Shader objects to attach and link.
   */
		void Compose(std::vector<Shader*> shaders);

		/**
   * @brief Gets the OpenGL program ID.
   * @return GLuint Program ID.
   */
		GLuint GetID() const { return mID; }

		/**
   * @brief Activates the shader program for use.
   */
		void Use();

		/**
   * @brief Sets a boolean uniform variable.
   * @param pName Name of the uniform variable.
   * @param pValue Boolean value to set.
   */
		void SetBool(const GLchar* pName, GLboolean pValue);

		/**
   * @brief Sets an integer uniform variable.
   * @param pName Name of the uniform variable.
   * @param pValue Integer value to set.
   */
		void SetInt(const GLchar* pName, GLint pValue);

		/**
   * @brief Sets a float uniform variable.
   * @param pName Name of the uniform variable.
   * @param pValue Float value to set.
   */
		void SetFloat(const GLchar* pName, GLfloat pValue);

		/**
   * @brief Sets a vec2 uniform variable from a Vector2.
   * @param pName Name of the uniform variable.
   * @param pValue Vector2 value to set.
   */
		void SetVec2f(const GLchar* pName, const Vector2& pValue);

		/**
   * @brief Sets a vec2 uniform variable from two floats.
   * @param pName Name of the uniform variable.
   * @param pX X component.
   * @param pY Y component.
   */
		void SetVec2f(const GLchar* pName, GLfloat pX, GLfloat pY);

		/**
   * @brief Sets a vec3 uniform variable from a Vector3.
   * @param pName Name of the uniform variable.
   * @param pValue Vector3 value to set.
   */
		void SetVec3f(const GLchar* pName, const Vector3& pValue);

		/**
   * @brief Sets a vec3 uniform variable from a Color.
   * @param pName Name of the uniform variable.
   * @param pValue Color value to set.
   */
		void SetVec3f(const GLchar* pName, const Color& pValue);

		/**
   * @brief Sets a vec3 uniform variable from three floats.
   * @param pName Name of the uniform variable.
   * @param pX X component.
   * @param pY Y component.
   * @param pZ Z component.
   */
		void SetVec3f(const GLchar* pName, GLfloat pX, GLfloat pY, GLfloat pZ);

		/**
   * @brief Sets a vec4 uniform variable from a Vector4.
   * @param pName Name of the uniform variable.
   * @param pValue Vector4 value to set.
   */
		void SetVec4f(const GLchar* pName, const Vector4& pValue);

		/**
   * @brief Sets a vec4 uniform variable from a Color.
   * @param pName Name of the uniform variable.
   * @param pValue Color value to set.
   */
		void SetVec4f(const GLchar* pName, const Color& pValue);

		/**
   * @brief Sets a vec4 uniform variable from four floats.
   * @param pName Name of the uniform variable.
   * @param pX X component.
   * @param pY Y component.
   * @param pZ Z component.
   * @param pW W component.
   */
		void SetVec4f(const GLchar* pName, GLfloat pX, GLfloat pY, GLfloat pZ, GLfloat pW);

		/**
   * @brief Sets a mat2 uniform variable.
   * @param pName Name of the uniform variable.
   * @param pMatrix 2x2 matrix to set.
   */
		void SetMat2(const GLchar* pName, const glm::mat2& pMatrix);

		/**
   * @brief Sets a mat3 uniform variable.
   * @param pName Name of the uniform variable.
   * @param pMatrix 3x3 matrix to set.
   */
		void SetMat3(const GLchar* pName, const glm::mat3& pMatrix);

		/**
   * @brief Sets a mat4 uniform variable from a Matrix4.
   * @param pName Name of the uniform variable.
   * @param pMatrix 4x4 matrix to set.
   */
		void SetMat4(const GLchar* pName, const Matrix4& pMatrix);

		/**
   * @brief Sets a mat4 uniform variable from a Matrix4Row.
   * @param pName Name of the uniform variable.
   * @param pMatrix 4x4 row-major matrix to set.
   */
		void SetMat4Row(const GLchar* pName, const Matrix4Row& pMatrix);
	};
}

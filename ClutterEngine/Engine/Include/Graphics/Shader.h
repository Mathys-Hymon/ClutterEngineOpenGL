#pragma once
#include <Core/CCommon.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

namespace clt
{
	class CLUTTER_API Shader
	{
		GLuint mID;
		std::string mVert_file_path, mFrag_file_path;

		void Compile(const GLchar* pVert_data, const GLchar* pFrag_data);

	public:
		Shader() : mID(0) {}
		~Shader()
		{
			if (mID) glDeleteProgram(mID);
			mID = 0;
		}

		void Load(const GLchar* pVert_file_path, const GLchar* pFrag_file_path);
		void Use();

		void SetBool(const GLchar* pName, GLboolean pValue);

		void SetInt(const GLchar* pName, GLint pValue);
		void SetFloat(const GLchar* pName, GLfloat pValue);

		void SetVec2f(const GLchar* pName, const glm::vec2& pValue);
		void SetVec2f(const GLchar* pName, GLfloat pX, GLfloat pY);

		void SetVec3f(const GLchar* pName, const glm::vec3& pValue);
		void SetVec3f(const GLchar* pName, GLfloat pX, GLfloat pY, GLfloat pZ);

		void SetVec4f(const GLchar* pName, const glm::vec4& pValue);
		void SetVec4f(const GLchar* pName, GLfloat pX, GLfloat pY, GLfloat pZ, GLfloat pW);

		void SetMat2(const GLchar* pName, const glm::mat2& pMatrix);
		void SetMat3(const GLchar* pName, const glm::mat3& pMatrix);
		void SetMat4(const GLchar* pName, const glm::mat4& pMatrix);
	};
}

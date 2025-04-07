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
	class CLUTTER_API ShaderProgram
	{
		GLuint mID;

	public :
		ShaderProgram();
		~ShaderProgram() = default;
		void Unload();
		void Compose(std::vector<Shader*> shaders);

		GLuint GetID() const { return mID; }

		void Use();

		void SetBool(const GLchar* pName, GLboolean pValue);

		void SetInt(const GLchar* pName, GLint pValue);
		void SetFloat(const GLchar* pName, GLfloat pValue);

		void SetVec2f(const GLchar* pName, const Vector2& pValue);
		void SetVec2f(const GLchar* pName, GLfloat pX, GLfloat pY);

		void SetVec3f(const GLchar* pName, const Vector3& pValue);
		void SetVec3f(const GLchar* pName, const Color& pValue);
		void SetVec3f(const GLchar* pName, GLfloat pX, GLfloat pY, GLfloat pZ);

		void SetVec4f(const GLchar* pName, const Vector4& pValue);
		void SetVec4f(const GLchar* pName, const Color& pValue);
		void SetVec4f(const GLchar* pName, GLfloat pX, GLfloat pY, GLfloat pZ, GLfloat pW);

		void SetMat2(const GLchar* pName, const glm::mat2& pMatrix);
		void SetMat3(const GLchar* pName, const glm::mat3& pMatrix);
		void SetMat4(const GLchar* pName, const Matrix4& pMatrix);
		void SetMat4Row(const GLchar* pName, const Matrix4Row& pMatrix);
	};
}
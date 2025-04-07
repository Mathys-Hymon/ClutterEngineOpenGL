#pragma once
#include <Core/CCommon.h>
#include <glad/glad.h>

#include <string>

namespace clt
{
	enum class CLUTTER_API ShaderType
	{
		VERTEX,
		FRAGMENT,	
	};

	class DebugDraw;
	class CLUTTER_API Shader
	{
	protected:
		GLuint mID;
		std::string mCode;
		ShaderType mType;

	public:
		Shader() : mID(0), mType(ShaderType::VERTEX) {}
		Shader(const GLchar* pFileName, ShaderType pShaderType) { Load(pFileName, pShaderType); }
		~Shader()
		{
			if (mID) glDeleteProgram(mID);
			mID = 0;
		}

		int GetID() const { return mID; }

		void Load(const GLchar* pFileName, ShaderType pShaderType);
		void Use();

		std::string GetCode() const { return mCode; };
	};
}

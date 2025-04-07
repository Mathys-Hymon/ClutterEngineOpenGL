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
		Shader(int pID, std::string pCode, ShaderType pShaderType) : mID(pID),mCode(pCode), mType(pShaderType) { Load(pCode, pShaderType); }
		~Shader()
		{
			if (mID) glDeleteProgram(mID);
			mID = 0;
		}

		int GetID() { return mID; }

		void Load(std::string pFileName, ShaderType pShaderType);
		void Use();

		const std::string GetCode() const { return mCode; };
	};
}

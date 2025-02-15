#pragma once
#include <Core/CLog/CLog.h>
#include <Core/Maths/Vectors/Vector2.h>
#include <filesystem>
#include <stdlib.h>
#include <stdexcept>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>


namespace clt
{
	class CInputManager;
	class CVertexArrayObject;
	class CUniformBuffer;
	class CShaderProgram;

	typedef std::shared_ptr<CVertexArrayObject> CVertexArrayObjectPtr;     // Shared pointer to a vertex array object
	typedef std::shared_ptr< CUniformBuffer	> CUniformBufferPtr;           // Shared pointer to a uniform buffer
	typedef std::shared_ptr< CShaderProgram > CShaderProgramPtr;            // Shared pointer to a shader program


	inline const char* contentPath(const wchar_t* path)
	{
		thread_local static std::string strPath;
		strPath = (std::filesystem::path(L"Content/") / path).string();

		return strPath.c_str();
	}

    inline const char* contentPath(const char* path)
    {
        thread_local static std::string strPath;
        strPath = (std::filesystem::path(L"Content/") / path).string();

        return strPath.c_str();
    }

    inline const char* enginePath(const char* path)
    {
        thread_local static std::string strPath;
		strPath = (std::filesystem::path("Content/Engine/") / path).string();

        return strPath.c_str();
    }

	inline const char* enginePath(const wchar_t* path)
	{
		thread_local static std::string strPath;
		strPath = (std::filesystem::path(L"Content/Engine/") / path).string();

		return strPath.c_str();
	}
}


// COMMON DATA TYPES

typedef float f32;                                                           // 32-bit float
typedef int i32;                                                            // 32-bit signed integer
typedef unsigned int uint32;                                               // 32-bit unsigned integer

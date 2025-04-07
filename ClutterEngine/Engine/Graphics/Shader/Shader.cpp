#include "pch.h"
#include <Graphics/Shader/Shader.h>
#include <sstream>
#include <fstream>

using namespace clt;

void Shader::Load(const GLchar* pFileName, ShaderType pShaderType)
{
    mType = pShaderType;
    std::string shaderCode;

    try
    {
        // Read shader files  
        std::ifstream shaderFile(pFileName);
        std::stringstream shaderSstream;

        shaderSstream << shaderFile.rdbuf();

        shaderFile.close();

        shaderCode = shaderSstream.str();
    }
    catch (std::exception e)
    {
        CLUTTER_ERROR("shader files failed to load");
        exit(1);
    }

    mCode = shaderCode;

    switch (mType)
    {
    case ShaderType::VERTEX:
        mID = glCreateShader(GL_VERTEX_SHADER);
        break;

    case ShaderType::FRAGMENT:
        mID = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    default:
        CLUTTER_WARNING("This shader type has not yet been implemented.");
        mID = glCreateShader(GL_VERTEX_SHADER);
        break;
    }

    const char* source = mCode.c_str();
    glShaderSource(mID, 1, &source, NULL);
    glCompileShader(mID);
}

void Shader::Use()
{
    glUseProgram(mID);
}
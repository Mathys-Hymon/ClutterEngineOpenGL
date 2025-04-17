#include "pch.h"
#include <Graphics/Shader/Shader.h>
#include <sstream>
#include <fstream>

using namespace clt;

void Shader::Load(std::string pFileName, ShaderType pShaderType, bool pPath)
{
    mType = pShaderType;

    if (!pPath)
    {
        mCode = pFileName;
    }
    else
    {
        std::ifstream file;
        file.open(pFileName);

        if (file.fail())
        {
            CLUTTER_WARNING(("shader files failed to load :" + pFileName).c_str());
            return;
        }

        std::string fileText = "";
        std::string line = "";

        while (std::getline(file, line))
        {
            fileText += line + '\n';
        }

        file.close();
        mCode = fileText;
    }

    switch (mType)
    {
    case ShaderType::VERTEX:
        mID = glCreateShader(GL_VERTEX_SHADER);
        break;

    case ShaderType::FRAGMENT:
        mID = glCreateShader(GL_FRAGMENT_SHADER);
        break;

    case ShaderType::TESSELATION_CONTROL:
        mID = glCreateShader(GL_TESS_CONTROL_SHADER);
        break;

    case ShaderType::TESSELATION_EVALUATION:
        mID = glCreateShader(GL_TESS_EVALUATION_SHADER);
        break;

    case ShaderType::GEOMETRY:
        mID = glCreateShader(GL_GEOMETRY_SHADER);
        break;

    default:
        CLUTTER_WARNING("This shader type has not yet been implemented.");
        mID = glCreateShader(GL_VERTEX_SHADER);
        break;
    }

    const char* source = mCode.c_str();
    glShaderSource(mID, 1, &source, NULL);
    glCompileShader(mID);

    if (!pPath) return;

    std::string temp = "shader files loaded sucessfully: " + pFileName;
    CLUTTER_INFO(temp.c_str());
}

void Shader::Use()
{
    glUseProgram(mID);
}
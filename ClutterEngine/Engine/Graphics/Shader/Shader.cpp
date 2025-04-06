#include "pch.h"
#include <Graphics/Shader/Shader.h>
#include <sstream>
#include <fstream>

using namespace clt;

void Shader::Compile(const GLchar* pVertData, const GLchar* pFragData)
{
    GLint success;
    GLchar info_log[512];

    GLuint vertexShader, fragShader;

    // Create and compile vertex shader  
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &pVertData, nullptr);
    glCompileShader(vertexShader);

    // Check for vertex shader compilation errors  
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, info_log);
        std::string error_message = "Vertex shader compilation failure, vertexShader = " + std::string(mVertPath) + "\n" + std::string(info_log);
        CLUTTER_ERROR(error_message.c_str());
        exit(1);
    }
    else CLUTTER_LOG("Vertex shader compiled succesfully");

    // Create and compile fragment shader  
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &pFragData, nullptr);
    glCompileShader(fragShader);

    // Check for fragment shader compilation errors  
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, nullptr, info_log);
        std::string error_message = "Fragment shader compilation failure, fragShader = " + std::string(mFragPath) + "\n" + std::string(info_log);
        CLUTTER_ERROR(error_message.c_str());
        exit(1);
    }
    else CLUTTER_LOG("Fragment shader compiled succesfully");

    mID = glCreateProgram();

    glAttachShader(mID, vertexShader);
    glAttachShader(mID, fragShader);

    glLinkProgram(mID);

    glGetProgramiv(mID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(mID, 512, nullptr, info_log);
        std::string error_message = "Program linking failure, vertex = \n" + std::string(mVertPath) + " \n fragShader = " + std::string(mFragPath) + "\n" + std::string(info_log);
        CLUTTER_ERROR(error_message.c_str());
        exit(1);
    }
    else CLUTTER_INFO("Shader Program linked");

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

void Shader::Load(const GLchar* pVertPath, const GLchar* pFragPath)
{
    mVertPath = pVertPath;
    mFragPath = pFragPath;

    std::string vertCode;
    std::string fragCode;

    try
    {
        // Read shader files  
        std::ifstream vertFile(pVertPath);
        std::ifstream fragFile(pFragPath);
        std::stringstream vertSstream, fragSstream;

        vertSstream << vertFile.rdbuf();
        fragSstream << fragFile.rdbuf();

        vertFile.close();
        fragFile.close();

        vertCode = vertSstream.str();
        fragCode = fragSstream.str();
    }
    catch (std::exception e)
    {
        CLUTTER_ERROR("shader files failed to load");
        exit(1);
    }

    Compile(vertCode.c_str(), fragCode.c_str());
}

void Shader::Use()
{
    glUseProgram(mID);
}

void Shader::SetBool(const GLchar* pName, GLboolean pValue)
{
    glUniform1i(glGetUniformLocation(mID, pName), pValue);
}

void Shader::SetInt(const GLchar* pName, GLint pValue)
{
    glUniform1i(glGetUniformLocation(mID, pName), pValue);
}

void Shader::SetFloat(const GLchar* pName, GLfloat pValue)
{
    glUniform1f(glGetUniformLocation(mID, pName), pValue);
}

void Shader::SetVec2f(const GLchar* pName, const Vector2& pValue)
{
    glUniform2f(glGetUniformLocation(mID, pName), pValue.x, pValue.y);
}

void Shader::SetVec2f(const GLchar* pName, GLfloat pX, GLfloat pY)
{
    glUniform2f(glGetUniformLocation(mID, pName), pX, pY);
}

void Shader::SetVec3f(const GLchar* pName, const Vector3& pValue)
{
    glUniform3f(glGetUniformLocation(mID, pName), pValue.x, pValue.y, pValue.z);
}

void Shader::SetVec3f(const GLchar* pName, const Color& pValue)
{
    glUniform3f(glGetUniformLocation(mID, pName), pValue.r, pValue.g, pValue.b);
}

void Shader::SetVec3f(const GLchar* pName, GLfloat pX, GLfloat pY, GLfloat pZ)
{
    glUniform3f(glGetUniformLocation(mID, pName), pX, pY, pZ);
}

void Shader::SetVec4f(const GLchar* pName, const Vector4& pValue)
{
    glUniform4f(glGetUniformLocation(mID, pName), pValue.x, pValue.y, pValue.z, pValue.w);
}

void Shader::SetVec4f(const GLchar* pName, const Color& pValue)
{
    glUniform4f(glGetUniformLocation(mID, pName), pValue.r, pValue.g, pValue.b, pValue.a);
}

void Shader::SetVec4f(const GLchar* pName, GLfloat pX, GLfloat pY, GLfloat pZ, GLfloat pW)
{
    glUniform4f(glGetUniformLocation(mID, pName), pX, pY, pZ, pW);
}

void Shader::SetMat2(const GLchar* pName, const glm::mat2& pMatrix)
{
    glUniformMatrix2fv(glGetUniformLocation(mID, pName), 1, GL_FALSE, &pMatrix[0][0]);
}

void Shader::SetMat3(const GLchar* pName, const glm::mat3& pMatrix)
{
    glUniformMatrix3fv(glGetUniformLocation(mID, pName), 1, GL_FALSE, &pMatrix[0][0]);
}

void Shader::SetMat4(const GLchar* pName, const Matrix4& pMatrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mID, pName), 1, GL_TRUE, pMatrix.GetAsFloatPtr());
}

void Shader::SetMat4Row(const GLchar* pName, const Matrix4Row& pMatrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mID, pName), 1, GL_TRUE, pMatrix.GetAsFloatPtr());
}
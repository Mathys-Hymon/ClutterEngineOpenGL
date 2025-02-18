#include "pch.h"
#include <Graphics/Shader.h>
#include <sstream>
#include <fstream>

using namespace clt;

void Shader::Compile(const GLchar* pVert_data, const GLchar* pFrag_data)
{
    GLint success;
    GLchar info_log[512];

    GLuint vertexShader, fragShader;

    // Create and compile vertex shader  
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &pVert_data, nullptr);
    glCompileShader(vertexShader);

    // Check for vertex shader compilation errors  
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, info_log);
        std::string error_message = "Vertex shader compilation failure, vertexShader = " + std::string(mVert_file_path) + "\n" + std::string(info_log);
        CLUTTER_ERROR(error_message.c_str());
        exit(1);
    }
    else CLUTTER_LOG("Vertex shader compiled succesfully");

    // Create and compile fragment shader  
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &pFrag_data, nullptr);
    glCompileShader(fragShader);

    // Check for fragment shader compilation errors  
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, nullptr, info_log);
        std::string error_message = "Fragment shader compilation failure, fragShader = " + std::string(mFrag_file_path) + "\n" + std::string(info_log);
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
        std::string error_message = "Program linking failure, vertex = \n" + std::string(mVert_file_path) + " \n fragShader = " + std::string(mFrag_file_path) + "\n" + std::string(info_log);
        CLUTTER_ERROR(error_message.c_str());
        exit(1);
    }
    else CLUTTER_INFO("Shader Program linked");

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

void Shader::Load(const GLchar* pVert_file_path, const GLchar* pFrag_file_path)
{
    mVert_file_path = pVert_file_path;
    mFrag_file_path = pFrag_file_path;

    std::string vert_code;
    std::string frag_code;

    try
    {
        // Read shader files  
        std::ifstream vert_file(pVert_file_path);
        std::ifstream frag_file(pFrag_file_path);
        std::stringstream vert_sstream, frag_sstream;

        vert_sstream << vert_file.rdbuf();
        frag_sstream << frag_file.rdbuf();

        vert_file.close();
        frag_file.close();

        vert_code = vert_sstream.str();
        frag_code = frag_sstream.str();
    }
    catch (std::exception e)
    {
        CLUTTER_ERROR("shader files failed to load");
        exit(1);
    }

    Compile(vert_code.c_str(), frag_code.c_str());
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

void Shader::SetVec2f(const GLchar* pName, const glm::vec2& pValue)
{
    glUniform2fv(glGetUniformLocation(mID, pName), 1, &pValue[0]);
}

void Shader::SetVec2f(const GLchar* pName, GLfloat pX, GLfloat pY)
{
    glUniform2f(glGetUniformLocation(mID, pName), pX, pY);
}

void Shader::SetVec3f(const GLchar* pName, const glm::vec3& pValue)
{
    glUniform3fv(glGetUniformLocation(mID, pName), 1, &pValue[0]);
}

void Shader::SetVec3f(const GLchar* pName, GLfloat pX, GLfloat pY, GLfloat pZ)
{
    glUniform3f(glGetUniformLocation(mID, pName), pX, pY, pZ);
}

void Shader::SetVec4f(const GLchar* pName, const glm::vec4& pValue)
{
    glUniform4fv(glGetUniformLocation(mID, pName), 1, &pValue[0]);
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

void Shader::SetMat4(const GLchar* pName, const glm::mat4& pMatrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mID, pName), 1, GL_FALSE, &pMatrix[0][0]);
}

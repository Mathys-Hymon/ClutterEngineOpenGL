#include "pch.h"
#include "ShaderProgram.h"

using namespace clt;

ShaderProgram::ShaderProgram() : mID(0)
{
}

void ShaderProgram::Unload()
{
    glDeleteProgram(mID);
}

void ShaderProgram::Compose(std::vector<Shader*> shaders)
{
    mShaders = shaders;
    mID = glCreateProgram();

    for (Shader* s : mShaders)
    {
        glAttachShader(mID, s->GetID());
    }

    glLinkProgram(mID);
    Use();

    GLint success;
    glGetProgramiv(mID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(mID, 512, NULL, infoLog);
        CLUTTER_WARNING(("Shader program linking failed: " + std::string(infoLog)).c_str());
    }
}

void ShaderProgram::Use()
{
    glUseProgram(mID);
}

void ShaderProgram::SetBool(const GLchar* pName, GLboolean pValue)
{
    glUniform1i(glGetUniformLocation(mID, pName), pValue);
}

void ShaderProgram::SetInt(const GLchar* pName, GLint pValue)
{
    glUniform1i(glGetUniformLocation(mID, pName), pValue);
}

void ShaderProgram::SetFloat(const GLchar* pName, GLfloat pValue)
{
    glUniform1f(glGetUniformLocation(mID, pName), pValue);
}

void ShaderProgram::SetVec2f(const GLchar* pName, const Vector2& pValue)
{
    glUniform2f(glGetUniformLocation(mID, pName), pValue.x, pValue.y);
}

void ShaderProgram::SetVec2f(const GLchar* pName, GLfloat pX, GLfloat pY)
{
    glUniform2f(glGetUniformLocation(mID, pName), pX, pY);
}

void ShaderProgram::SetVec3f(const GLchar* pName, const Vector3& pValue)
{
    glUniform3f(glGetUniformLocation(mID, pName), pValue.x, pValue.y, pValue.z);
}

void ShaderProgram::SetVec3f(const GLchar* pName, const Color& pValue)
{
    glUniform3f(glGetUniformLocation(mID, pName), pValue.r, pValue.g, pValue.b);
}

void ShaderProgram::SetVec3f(const GLchar* pName, GLfloat pX, GLfloat pY, GLfloat pZ)
{
    glUniform3f(glGetUniformLocation(mID, pName), pX, pY, pZ);
}

void ShaderProgram::SetVec4f(const GLchar* pName, const Vector4& pValue)
{
    glUniform4f(glGetUniformLocation(mID, pName), pValue.x, pValue.y, pValue.z, pValue.w);
}

void ShaderProgram::SetVec4f(const GLchar* pName, const Color& pValue)
{
    glUniform4f(glGetUniformLocation(mID, pName), pValue.r, pValue.g, pValue.b, pValue.a);
}

void ShaderProgram::SetVec4f(const GLchar* pName, GLfloat pX, GLfloat pY, GLfloat pZ, GLfloat pW)
{
    glUniform4f(glGetUniformLocation(mID, pName), pX, pY, pZ, pW);
}

void ShaderProgram::SetMat2(const GLchar* pName, const glm::mat2& pMatrix)
{
    glUniformMatrix2fv(glGetUniformLocation(mID, pName), 1, GL_FALSE, &pMatrix[0][0]);
}

void ShaderProgram::SetMat3(const GLchar* pName, const glm::mat3& pMatrix)
{
    glUniformMatrix3fv(glGetUniformLocation(mID, pName), 1, GL_FALSE, &pMatrix[0][0]);
}

void ShaderProgram::SetMat4(const GLchar* pName, const Matrix4& pMatrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mID, pName), 1, GL_TRUE, pMatrix.GetAsFloatPtr());
}

void ShaderProgram::SetMat4Row(const GLchar* pName, const Matrix4Row& pMatrix)
{
    glUniformMatrix4fv(glGetUniformLocation(mID, pName), 1, GL_TRUE, pMatrix.GetAsFloatPtr());
}
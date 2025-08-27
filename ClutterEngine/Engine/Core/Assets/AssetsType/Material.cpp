#include "pch.h"
#include "Material.h"

using namespace clt;

Material::Material(ShaderProgram* shaderProgram, std::vector<Shader*> shaders) : mShader(shaderProgram)
{
	mShader->Compose(shaders);
}

void Material::SetShader(ShaderProgram* shaderprogram, std::vector<Shader*> shaders)
{
	mShader = shaderprogram;
	mShader->Compose(shaders);
}

void Material::Apply()
{
	if (!mShader) return;

	mShader->Use();

	for (const auto& [name, value] : mFloatUniforms)
		mShader->SetFloat(name.c_str(), value);

	for (const auto& [name, value] : mIntUniforms)
		mShader->SetInt(name.c_str(), value);

	for (const auto& [name, value] : mVec2Uniforms)
		mShader->SetVec2f(name.c_str(), value);

	for (const auto& [name, value] : mVec3Uniforms)
		mShader->SetVec3f(name.c_str(), value);

	for (const auto& [name, value] : mVec4Uniforms)
		mShader->SetVec4f(name.c_str(), value);

	for (const auto& [name, color] : mColorUniforms)
		mShader->SetVec3f(name.c_str(), color);

	for (const auto& [name, mat2] : mMat2Uniforms)
		mShader->SetMat2(name.c_str(), mat2);

	for (const auto& [name, mat3] : mMat3Uniforms)
		mShader->SetMat3(name.c_str(), mat3);

	for (const auto& [name, mat4Row] : mMat4RowUniforms)
		mShader->SetMat4Row(name.c_str(), mat4Row);

	for (const auto& [name, mat4] : mMat4Uniforms)
		mShader->SetMat4(name.c_str(), mat4);

	for (const auto& [name, texture] : mTextureUniforms)
	{
		if (texture)
		{
			texture->Bind(0);
		}
	}
}

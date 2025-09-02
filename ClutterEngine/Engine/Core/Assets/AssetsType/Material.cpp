#include "pch.h"
#include "Material.h"

using namespace clt;

Material::Material(std::vector<Shader*> shaders) : mShader(nullptr)
{
	mShader = new ShaderProgram();
	mShader->Compose(shaders);
}

void Material::SetShader(std::vector<Shader*> shaders)
{
	if(!mShader)	mShader = new ShaderProgram();
	else mShader->Unload();

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
		auto tempTex = texture.lock();

		if (tempTex)
		{
			tempTex->Bind(0);
		}
	}
}

bool Material::HasFloat(const std::string& name) const
{
	return mFloatUniforms.find(name) != mFloatUniforms.end();
}

float Material::GetFloat(const std::string& name) const
{
	auto it = mFloatUniforms.find(name);
	return it != mFloatUniforms.end() ? it->second : 0.0f;
}

bool Material::HasInt(const std::string& name) const
{
	return mIntUniforms.find(name) != mIntUniforms.end();
}

int Material::GetInt(const std::string& name) const
{
	auto it = mIntUniforms.find(name);
	return it != mIntUniforms.end() ? it->second : 0;
}

bool Material::HasVec2(const std::string& name) const
{
	return mVec2Uniforms.find(name) != mVec2Uniforms.end();
}

Vector2 Material::GetVec2(const std::string& name) const
{
	auto it = mVec2Uniforms.find(name);
	return it != mVec2Uniforms.end() ? it->second : Vector2::Zero;
}

bool Material::HasVec3(const std::string& name) const
{
	return mVec3Uniforms.find(name) != mVec3Uniforms.end();
}

Vector3 Material::GetVec3(const std::string& name) const
{
	auto it = mVec3Uniforms.find(name);
	return it != mVec3Uniforms.end() ? it->second : Vector3::Zero;
}

bool Material::HasVec4(const std::string& name) const
{
	return mVec4Uniforms.find(name) != mVec4Uniforms.end();
}

Vector4 Material::GetVec4(const std::string& name) const
{
	auto it = mVec4Uniforms.find(name);
	return it != mVec4Uniforms.end() ? it->second : Vector4::Zero;
}

bool Material::HasColor(const std::string& name) const
{
	return mColorUniforms.find(name) != mColorUniforms.end();
}

Color Material::GetColor(const std::string& name) const
{
	auto it = mColorUniforms.find(name);
	return it != mColorUniforms.end() ? it->second : Color::Black;
}

bool Material::HasTexture(const std::string& name) const
{
	return mTextureUniforms.find(name) != mTextureUniforms.end();
}

std::weak_ptr<Texture> Material::GetTexture(const std::string& name) const
{
	auto it = mTextureUniforms.find(name);
	return it != mTextureUniforms.end() ? it->second : std::weak_ptr<Texture>();
}

bool Material::HasTexture(std::weak_ptr<Texture> texture) const
{
	if (!texture.lock()) return false;

	for (const auto& [name, texPtr] : mTextureUniforms)
	{
		if (texPtr.lock() == texture.lock())
			return true;
	}
	return false;
}

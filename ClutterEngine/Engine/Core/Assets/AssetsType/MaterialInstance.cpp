#include "pch.h"
#include "MaterialInstance.h"

using namespace clt;

void MaterialInstance::Apply()
{
	if (!mBaseMaterial)
		return;

	ShaderProgram* shader = mBaseMaterial->GetShader();
	if (!shader)
		return;

	shader->Use();

	// Apply float
	for (const auto& [name, val] : mBaseMaterial->GetFloatUniforms())
		shader->SetFloat(name.c_str(), mFloatOverrides.count(name) ? mFloatOverrides[name] : val);

	// Apply Int
	for (const auto& [name, val] : mBaseMaterial->GetIntUniforms())
		shader->SetInt(name.c_str(), mIntOverrides.count(name) ? mIntOverrides[name] : val);

	// Apply vec2
	for (const auto& [name, val] : mBaseMaterial->GetVec2Uniforms())
		shader->SetVec2f(name.c_str(), mVec2Overrides.count(name) ? mVec2Overrides[name] : val);

	// Apply vec3
	for (const auto& [name, val] : mBaseMaterial->GetVec3Uniforms())
		shader->SetVec3f(name.c_str(), mVec3Overrides.count(name) ? mVec3Overrides[name] : val);

	// Apply vec4
	for (const auto& [name, val] : mBaseMaterial->GetVec4Uniforms())
		shader->SetVec4f(name.c_str(), mVec4Overrides.count(name) ? mVec4Overrides[name] : val);

	// Apply colors
	for (const auto& [name, val] : mBaseMaterial->GetColorUniforms())
		shader->SetVec3f(name.c_str(), mColorOverrides.count(name) ? mColorOverrides[name] : val);

	// Apply textures
	int unit = 0;
	for (const auto& [name, val] : mBaseMaterial->GetTextureUniforms())
	{
		auto tex = mTextureOverrides.count(name) ? mTextureOverrides[name].lock() : val.lock();

		if (tex)
		{
			tex->Bind(unit);
			shader->SetInt(name.c_str(), unit);
			unit++;
		}
	}
}

const std::unordered_map<std::string, std::weak_ptr<Texture>>& MaterialInstance::GetTextureUniforms() const
{
	std::unordered_map<std::string, std::weak_ptr<Texture>> tempMap;

	for (const auto& [name, val] : mBaseMaterial->GetTextureUniforms())
		tempMap[name] = mTextureOverrides.count(name) ? mTextureOverrides.at(name) : val;

	return tempMap;
}

bool clt::MaterialInstance::HasTexture(std::weak_ptr<Texture> texture) const
{
	if (!texture.lock()) return false;

	for (const auto& [name, texPtr] : mTextureOverrides)
	{
		if (texPtr.lock() == texture.lock())
			return true;
	}
	return mBaseMaterial->HasTexture(texture);
}

bool clt::MaterialInstance::HasTexture(const std::string& texture) const
{
	return (mTextureOverrides.find(texture) != mTextureOverrides.end() || mBaseMaterial->HasTexture(texture));
}

std::weak_ptr<Texture> clt::MaterialInstance::GetTexture(const std::string& name) const
{
	return std::weak_ptr<Texture>();
}

const std::unordered_map<std::string, float>& clt::MaterialInstance::GetFloatUniforms() const
{
	std::unordered_map<std::string, float> tempMap;

	for (const auto& [name, val] : mBaseMaterial->GetFloatUniforms())
		tempMap[name] = mFloatOverrides.count(name) ? mFloatOverrides.at(name) : val;

	return tempMap;
}

bool clt::MaterialInstance::HasFloat(const std::string& name) const
{
	return (mFloatOverrides.find(name) != mFloatOverrides.end() || mBaseMaterial->HasFloat(name));
}

float clt::MaterialInstance::GetFloat(const std::string& name) const
{
	return 0.0f;
}

const std::unordered_map<std::string, int>& clt::MaterialInstance::GetIntUniforms() const
{
	std::unordered_map<std::string, int> tempMap;

	for (const auto& [name, val] : mBaseMaterial->GetIntUniforms())
		tempMap[name] = mIntOverrides.count(name) ? mIntOverrides.at(name) : val;

	return tempMap;
}

bool clt::MaterialInstance::HasInt(const std::string& name) const
{
	return (mIntOverrides.find(name) != mIntOverrides.end() || mBaseMaterial->HasInt(name));
}

int clt::MaterialInstance::GetInt(const std::string& name) const
{
	return 0;
}

const std::unordered_map<std::string, Vector2>& clt::MaterialInstance::GetVec2Uniforms() const
{
	std::unordered_map<std::string, Vector2> tempMap;

	for (const auto& [name, val] : mBaseMaterial->GetVec2Uniforms())
		tempMap[name] = mVec2Overrides.count(name) ? mVec2Overrides.at(name) : val;

	return tempMap;
}

bool clt::MaterialInstance::HasVec2(const std::string& name) const
{
	return (mVec2Overrides.find(name) != mVec2Overrides.end() || mBaseMaterial->HasVec2(name));
}

Vector2 clt::MaterialInstance::GetVec2(const std::string& name) const
{
	return Vector2();
}

const std::unordered_map<std::string, Vector3>& clt::MaterialInstance::GetVec3Uniforms() const
{
	std::unordered_map<std::string, Vector3> tempMap;

	for (const auto& [name, val] : mBaseMaterial->GetVec3Uniforms())
		tempMap[name] = mVec3Overrides.count(name) ? mVec3Overrides.at(name) : val;

	return tempMap;
}

bool clt::MaterialInstance::HasVec3(const std::string& name) const
{
	return (mVec3Overrides.find(name) != mVec3Overrides.end() || mBaseMaterial->HasVec3(name));
}

Vector3 clt::MaterialInstance::GetVec3(const std::string& name) const
{
	return Vector3();
}

const std::unordered_map<std::string, Vector4>& clt::MaterialInstance::GetVec4Uniforms() const
{
	std::unordered_map<std::string, Vector4> tempMap;

	for (const auto& [name, val] : mBaseMaterial->GetVec4Uniforms())
		tempMap[name] = mVec4Overrides.count(name) ? mVec4Overrides.at(name) : val;

	return tempMap;
}

bool clt::MaterialInstance::HasVec4(const std::string& name) const
{
	return (mVec4Overrides.find(name) != mVec4Overrides.end() || mBaseMaterial->HasVec4(name));
}

Vector4 clt::MaterialInstance::GetVec4(const std::string& name) const
{
	return Vector4();
}

const std::unordered_map<std::string, Color>& clt::MaterialInstance::GetColorUniforms() const
{
	std::unordered_map<std::string, Color> tempMap;

	for (const auto& [name, val] : mBaseMaterial->GetColorUniforms())
		tempMap[name] = mColorOverrides.count(name) ? mColorOverrides.at(name) : val;

	return tempMap;
}

bool clt::MaterialInstance::HasColor(const std::string& name) const
{
	return (mColorOverrides.find(name) != mColorOverrides.end() || mBaseMaterial->HasColor(name));
}

Color clt::MaterialInstance::GetColor(const std::string& name) const
{
	return Color();
}

ShaderProgram* clt::MaterialInstance::GetShader() const
{
	return mBaseMaterial->GetShader();
}

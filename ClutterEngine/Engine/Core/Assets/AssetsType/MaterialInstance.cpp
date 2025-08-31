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

bool clt::MaterialInstance::HasTexture(std::weak_ptr<Texture> texture) const
{
	return false;
}

bool clt::MaterialInstance::HasTexture(const std::string& texture) const
{
	return false;
}

std::weak_ptr<Texture> clt::MaterialInstance::GetTexture(const std::string& name) const
{
	return std::weak_ptr<Texture>();
}

ShaderProgram* clt::MaterialInstance::GetShader() const
{
	return nullptr;
}

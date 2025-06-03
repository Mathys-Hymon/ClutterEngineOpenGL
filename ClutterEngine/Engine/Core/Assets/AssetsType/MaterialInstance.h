#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/AssetsType/Material.h>

namespace clt
{
	class CLUTTER_API MaterialInstance
	{
		Material* mBaseMaterial;

		std::unordered_map<std::string, float> mFloatOverrides;
		std::unordered_map<std::string, float> mIntOverrides;
		std::unordered_map<std::string, Vector2> mVec2Overrides;
		std::unordered_map<std::string, Vector3> mVec3Overrides;
		std::unordered_map<std::string, Vector4> mVec4Overrides;
		std::unordered_map<std::string, Color> mColorOverrides;
		std::unordered_map<std::string, Texture*> mTextureOverrides;

	public :
		MaterialInstance(Material* baseMaterial) : mBaseMaterial(baseMaterial) {};
		~MaterialInstance() = default;

		void SetFloat(const std::string& name, float value) { mFloatOverrides[name] = value; }
		void SetVec2(const std::string& name, const Vector2& value) { mVec2Overrides[name] = value; }
		void SetVec3(const std::string& name, const Vector3& value) { mVec3Overrides[name] = value; }
		void SetVec4(const std::string& name, const Vector4& value) { mVec4Overrides[name] = value; }
		void SetColor(const std::string& name, const Color& value) { mColorOverrides[name] = value; }
		void SetTexture(const std::string& name, Texture* texture) { mTextureOverrides[name] = texture; }

		void Apply()
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
				Texture* tex = mTextureOverrides.count(name) ? mTextureOverrides[name] : val;
				if (tex)
				{
					tex->Bind(unit);
					shader->SetInt(name.c_str(), unit);
					unit++;
				}
			}
		}
	};
}
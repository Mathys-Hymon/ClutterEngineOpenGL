#pragma once
#include <Core/CCommon.h>
#include <Graphics/Shader/ShaderProgram.h>
#include <Core/Assets/AssetsType/Texture.h>
#include <unordered_map>

namespace clt
{
	class CLUTTER_API Material
	{
		ShaderProgram* mShader = nullptr;

		std::unordered_map<std::string, float> mFloatUniforms;
		std::unordered_map<std::string, int> mIntUniforms;
		std::unordered_map<std::string, Vector2> mVec2Uniforms;
		std::unordered_map<std::string, Vector3> mVec3Uniforms;
		std::unordered_map<std::string, Vector4> mVec4Uniforms;
		std::unordered_map<std::string, Color> mColorUniforms;
		std::unordered_map<std::string, Texture*> mTextureUniforms;

	public :
		Material(ShaderProgram* shader) : mShader(shader) {};
		~Material() = default;

		void SetFloat(const std::string& name, float value) { mFloatUniforms[name] = value; }
		void SetInt(const std::string& name, int value) { mIntUniforms[name] = value; }
		void SetVec2(const std::string& name, const Vector2& value) { mVec2Uniforms[name] = value; }
		void SetVec3(const std::string& name, const Vector3& value) { mVec3Uniforms[name] = value; }
		void SetVec4(const std::string& name, const Vector4& value) { mVec4Uniforms[name] = value; }
		void SetColor(const std::string& name, const Color& value) { mColorUniforms[name] = value; }
		void SetTexture(const std::string& name, Texture* texture) { mTextureUniforms[name] = texture; }
		void SetShader(ShaderProgram* shader) { mShader = shader; }

		void Apply()
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

			int textureUnit = 0;
			for (const auto& [name, texture] : mTextureUniforms)
			{
				if (texture)
				{
					texture->Bind(textureUnit);
					mShader->SetInt(name.c_str(), textureUnit);
					textureUnit++;
				}
			}
		}

		ShaderProgram* GetShader() const { return mShader; }

		const std::unordered_map<std::string, float>& GetFloatUniforms() const { return mFloatUniforms; }
		bool HasFloat(const std::string& name) const { return mFloatUniforms.find(name) != mFloatUniforms.end(); }
		float GetFloat(const std::string& name) const {
			auto it = mFloatUniforms.find(name);
			return it != mFloatUniforms.end() ? it->second : 0.0f;
		}

		const std::unordered_map<std::string, int>& GetIntUniforms() const { return mIntUniforms; }
		bool HasInt(const std::string& name) const { return mIntUniforms.find(name) != mIntUniforms.end(); }
		int GetInt(const std::string& name) const {
			auto it = mIntUniforms.find(name);
			return it != mIntUniforms.end() ? it->second : 0;
		}

		const std::unordered_map<std::string, Vector2>& GetVec2Uniforms() const { return mVec2Uniforms; }
		bool HasVec2(const std::string& name) const { return mVec2Uniforms.find(name) != mVec2Uniforms.end(); }
		Vector2 GetVec2(const std::string& name) const {
			auto it = mVec2Uniforms.find(name);
			return it != mVec2Uniforms.end() ? it->second : Vector2{};
		}

		const std::unordered_map<std::string, Vector3>& GetVec3Uniforms() const { return mVec3Uniforms; }
		bool HasVec3(const std::string& name) const { return mVec3Uniforms.find(name) != mVec3Uniforms.end(); }
		Vector3 GetVec3(const std::string& name) const {
			auto it = mVec3Uniforms.find(name);
			return it != mVec3Uniforms.end() ? it->second : Vector3{};
		}

		const std::unordered_map<std::string, Vector4>& GetVec4Uniforms() const { return mVec4Uniforms; }
		bool HasVec4(const std::string& name) const { return mVec4Uniforms.find(name) != mVec4Uniforms.end(); }
		Vector4 GetVec4(const std::string& name) const {
			auto it = mVec4Uniforms.find(name);
			return it != mVec4Uniforms.end() ? it->second : Vector4{};
		}

		const std::unordered_map<std::string, Color>& GetColorUniforms() const { return mColorUniforms; }
		bool HasColor(const std::string& name) const { return mColorUniforms.find(name) != mColorUniforms.end(); }
		Color GetColor(const std::string& name) const {
			auto it = mColorUniforms.find(name);
			return it != mColorUniforms.end() ? it->second : Color{};
		}

		const std::unordered_map<std::string, Texture*>& GetTextureUniforms() const { return mTextureUniforms; }
		bool HasTexture(const std::string& name) const { return mTextureUniforms.find(name) != mTextureUniforms.end(); }
		Texture* GetTexture(const std::string& name) const {
			auto it = mTextureUniforms.find(name);
			return it != mTextureUniforms.end() ? it->second : nullptr;
		}
	};
}
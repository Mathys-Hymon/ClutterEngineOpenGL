#pragma once
#include <Core/CCommon.h>
#include <Graphics/Shader/ShaderProgram.h>
#include <Core/Assets/AssetsType/Texture.h>
#include <Core/Assets/AssetsType/IMaterial.h>
#include <unordered_map>

namespace clt
{
	class CLUTTER_API Material : public IMaterial
	{
		ShaderProgram* mShader = nullptr;

		std::unordered_map<std::string, float> mFloatUniforms;
		std::unordered_map<std::string, int> mIntUniforms;
		std::unordered_map<std::string, Vector2> mVec2Uniforms;
		std::unordered_map<std::string, Vector3> mVec3Uniforms;
		std::unordered_map<std::string, Vector4> mVec4Uniforms;
		std::unordered_map<std::string, Color> mColorUniforms;
		std::unordered_map<std::string, std::weak_ptr<Texture>> mTextureUniforms;
		std::unordered_map<std::string, glm::mat2> mMat2Uniforms;
		std::unordered_map<std::string, glm::mat3> mMat3Uniforms;
		std::unordered_map<std::string, Matrix4> mMat4Uniforms;
		std::unordered_map<std::string, Matrix4Row> mMat4RowUniforms;

	public :
		Material() = default;
		Material(ShaderProgram* shaderProgram) : mShader(shaderProgram) {};
		Material(std::vector <std::weak_ptr<Shader>> shaders);

		~Material() = default;

		void SetFloat(const std::string& name, float value)				  override { mFloatUniforms[name] = value; }
		void SetInt(const std::string& name, int value)					  override { mIntUniforms[name] = value; }
		void SetVec2(const std::string& name, const Vector2& value)		  override { mVec2Uniforms[name] = value; };
		void SetVec3(const std::string& name, const Vector3& value)		  override { mVec3Uniforms[name] = value; };
		void SetVec4(const std::string& name, const Vector4& value)		  override { mVec4Uniforms[name] = value; };
		void SetColor(const std::string& name, const Color& value)		  override { mColorUniforms[name] = value; };
		void SetTexture(const std::string& name, std::weak_ptr<Texture> texture)	      override { mTextureUniforms[name] = texture; };
		void SetMat2(const std::string& name, const glm::mat2& value)	  override {	mMat2Uniforms[name] = value; };
		void SetMat3(const std::string& name, const glm::mat3& value)	  override { mMat3Uniforms[name] = value; };
		void SetMat4(const std::string& name, const Matrix4& value)		  override { mMat4Uniforms[name] = value; };
		void SetMat4Row(const std::string& name, const Matrix4Row& value) override { mMat4RowUniforms[name] = value; };

		void SetShader(ShaderProgram* shaderProgram) { mShader = shaderProgram; }
		void SetShader(std::vector< std::weak_ptr<Shader>> shaders);

		void Apply();

		ShaderProgram* GetShader() const override { return mShader; }

		const std::unordered_map<std::string, float>& GetFloatUniforms() const override { return mFloatUniforms; }
		bool HasFloat(const std::string& name) const override;
		float GetFloat(const std::string& name) const override;

		const std::unordered_map<std::string, int>& GetIntUniforms() const override { return mIntUniforms; }
		bool HasInt(const std::string& name) const override;
		int GetInt(const std::string& name) const override;

		const std::unordered_map<std::string, Vector2>& GetVec2Uniforms() const override { return mVec2Uniforms; }
		bool HasVec2(const std::string& name) const override;
		Vector2 GetVec2(const std::string& name) const override;

		const std::unordered_map<std::string, Vector3>& GetVec3Uniforms() const override { return mVec3Uniforms; }
		bool HasVec3(const std::string& name) const override;
		Vector3 GetVec3(const std::string& name) const override;

		const std::unordered_map<std::string, Vector4>& GetVec4Uniforms() const override { return mVec4Uniforms; }
		bool HasVec4(const std::string& name) const override;
		Vector4 GetVec4(const std::string& name) const override;

		const std::unordered_map<std::string, Color>& GetColorUniforms() const override { return mColorUniforms; }
		bool HasColor(const std::string& name) const override;
		Color GetColor(const std::string& name) const override;

		const std::unordered_map<std::string, std::weak_ptr<Texture>>& GetTextureUniforms() const override { return mTextureUniforms; }
		bool HasTexture(const std::string& name) const override;
		std::weak_ptr<Texture> GetTexture(const std::string& name) const override;

		bool HasTexture(std::weak_ptr <Texture> texture) const override;

		Vector2 GetVec2(const std::string& name) const override;
	};
}
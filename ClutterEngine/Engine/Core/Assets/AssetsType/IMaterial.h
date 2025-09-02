#pragma once
#include <Core/CCommon.h>
#include <Graphics/Shader/ShaderProgram.h>
#include <unordered_map>
#include <Core/Maths/Vectors/Vector2.h>
#include <Core/Maths/Vectors/Vector3.h>

namespace clt
{
	class CLUTTER_API IMaterial
	{
	public:
		virtual void Apply() = 0;

		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetVec2(const std::string& name, const Vector2& value) = 0;
		virtual void SetVec3(const std::string& name, const Vector3& value) = 0;
		virtual void SetVec4(const std::string& name, const Vector4& value) = 0;
		virtual void SetColor(const std::string& name, const Color& value) = 0;
		virtual void SetTexture(const std::string& name, std::weak_ptr<Texture> texture) = 0;
		virtual void SetMat2(const std::string& name, const glm::mat2& value) = 0;
		virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void SetMat4(const std::string& name, const Matrix4& value) = 0;
		virtual void SetMat4Row(const std::string& name, const Matrix4Row& value) = 0;

		virtual const std::unordered_map<std::string, std::weak_ptr<Texture>>& GetTextureUniforms() const = 0;
		virtual bool HasTexture(std::weak_ptr<Texture> texture) const = 0;
		virtual bool HasTexture(const std::string& texture) const = 0;
		virtual std::weak_ptr<Texture> GetTexture(const std::string& name) const = 0;

		virtual const std::unordered_map<std::string, float>& GetFloatUniforms() const = 0;
		virtual bool HasFloat(const std::string& name) const = 0;
		virtual float GetFloat(const std::string& name) const = 0;

		virtual const std::unordered_map<std::string, int>& GetIntUniforms() const = 0;
		virtual bool HasInt(const std::string& name) const = 0;
		virtual int GetInt(const std::string& name) const = 0;

		virtual const std::unordered_map<std::string, Vector2>& GetVec2Uniforms() const = 0;
		virtual bool HasVec2(const std::string& name) const = 0;
		virtual Vector2 GetVec2(const std::string& name) const = 0;

		virtual const std::unordered_map<std::string, Vector3>& GetVec3Uniforms() const = 0;
		virtual bool HasVec3(const std::string& name) const = 0;
		virtual Vector3 GetVec3(const std::string& name) const = 0;

		virtual const std::unordered_map<std::string, Vector4>& GetVec4Uniforms() const = 0;
		virtual bool HasVec4(const std::string& name) const = 0;
		virtual Vector4 GetVec4(const std::string& name) const = 0;

		virtual const std::unordered_map<std::string, Color>& GetColorUniforms() const = 0;
		virtual bool HasColor(const std::string& name) const = 0;
		virtual Color GetColor(const std::string& name) const = 0;

		virtual ShaderProgram* GetShader() const = 0;
	};
}
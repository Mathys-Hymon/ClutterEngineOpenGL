#pragma once
#include <Core/CCommon.h>
#include <Graphics/Shader/ShaderProgram.h>

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

		virtual bool HasTexture(std::weak_ptr<Texture> texture) const = 0;
		virtual bool HasTexture(const std::string& texture) const = 0;

		virtual std::weak_ptr<Texture> GetTexture(const std::string& name) const = 0;
		virtual ShaderProgram* GetShader() const = 0;
	};
}
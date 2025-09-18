#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/AssetsType/Material.h>
#include <unordered_map>

namespace clt
{
	class CLUTTER_API MaterialInstance : public IMaterial
	{
		std::shared_ptr<IMaterial> mBaseMaterial;

		std::unordered_map<std::string, float> mFloatOverrides;
		std::unordered_map<std::string, int> mIntOverrides;
		std::unordered_map<std::string, Vector2> mVec2Overrides;
		std::unordered_map<std::string, Vector3> mVec3Overrides;
		std::unordered_map<std::string, Vector4> mVec4Overrides;
		std::unordered_map<std::string, Color> mColorOverrides;
		std::unordered_map<std::string, std::weak_ptr<Texture>> mTextureOverrides;
		std::unordered_map<std::string, glm::mat2> mMat2Overrides;
		std::unordered_map<std::string, glm::mat3> mMat3Overrides;
		std::unordered_map<std::string, Matrix4> mMat4Overrides;
		std::unordered_map<std::string, Matrix4Row> mMat4RowOverrides;

	public :
		MaterialInstance(std::shared_ptr<IMaterial> baseMaterial) : mBaseMaterial(baseMaterial) {};
		~MaterialInstance() = default;

		void Apply() override;

		void SetFloat(const std::string& name, float value)						 override { mFloatOverrides[name] = value;     };
		void SetInt(const std::string& name, int value)							 override { mIntOverrides[name] = value;       };
		void SetVec2(const std::string& name, const Vector2& value)				 override { mVec2Overrides[name] = value;      };
		void SetVec3(const std::string& name, const Vector3& value)			     override { mVec3Overrides[name] = value;      };
		void SetVec4(const std::string& name, const Vector4& value)			     override { mVec4Overrides[name] = value;      };
		void SetColor(const std::string& name, const Color& value)			     override { mColorOverrides[name] = value;     };
		void SetTexture(const std::string& name, std::weak_ptr<Texture> texture) override { mTextureOverrides[name] = texture; };
		void SetMat2(const std::string& name, const glm::mat2& value)			 override { mMat2Overrides[name] = value;	   };
		void SetMat3(const std::string& name, const glm::mat3& value)			 override { mMat3Overrides[name] = value;       };
		void SetMat4(const std::string& name, const Matrix4& value)				 override { mMat4Overrides[name] = value;       };
		void SetMat4Row(const std::string& name, const Matrix4Row& value)		 override { mMat4RowOverrides[name] = value;    };

		const std::unordered_map<std::string, std::weak_ptr<Texture>>& GetTextureUniforms() const override;
		bool HasTexture(std::weak_ptr<Texture> texture) const override;
		bool HasTexture(const std::string& texture) const override;
		std::weak_ptr<Texture> GetTexture(const std::string& name) const override;

		const std::unordered_map<std::string, float>& GetFloatUniforms() const override;
		bool HasFloat(const std::string& name) const override;
		float GetFloat(const std::string& name) const override;

		const std::unordered_map<std::string, int>& GetIntUniforms() const override;
		bool HasInt(const std::string& name) const override;
		int GetInt(const std::string& name) const override;

		const std::unordered_map<std::string, Vector2>& GetVec2Uniforms() const override;
		bool HasVec2(const std::string& name) const override;
		Vector2 GetVec2(const std::string& name) const override;

		const std::unordered_map<std::string, Vector3>& GetVec3Uniforms() const override;
		bool HasVec3(const std::string& name) const override;
		Vector3 GetVec3(const std::string& name) const override;

		const std::unordered_map<std::string, Vector4>& GetVec4Uniforms() const override;
		bool HasVec4(const std::string& name) const override;
		Vector4 GetVec4(const std::string& name) const override;

		const std::unordered_map<std::string, Color>& GetColorUniforms() const override;
		bool HasColor(const std::string& name) const override;
		Color GetColor(const std::string& name) const override;

		ShaderProgram* GetShader() const override;
	};
}
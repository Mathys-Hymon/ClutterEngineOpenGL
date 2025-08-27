#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/AssetsType/Material.h>
#include <unordered_map>

namespace clt
{
	class CLUTTER_API MaterialInstance : public IMaterial
	{
		Material* mBaseMaterial;

		std::unordered_map<std::string, float> mFloatOverrides;
		std::unordered_map<std::string, int> mIntOverrides;
		std::unordered_map<std::string, Vector2> mVec2Overrides;
		std::unordered_map<std::string, Vector3> mVec3Overrides;
		std::unordered_map<std::string, Vector4> mVec4Overrides;
		std::unordered_map<std::string, Color> mColorOverrides;
		std::unordered_map<std::string, Texture*> mTextureOverrides;
		std::unordered_map<std::string, glm::mat2> mMat2Uniforms;
		std::unordered_map<std::string, glm::mat3> mMat3Uniforms;
		std::unordered_map<std::string, Matrix4> mMat4Uniforms;
		std::unordered_map<std::string, Matrix4Row> mMat4RowUniforms;

	public :
		MaterialInstance(Material* baseMaterial) : mBaseMaterial(baseMaterial) {};
		~MaterialInstance() = default;

		void SetFloat(const std::string& name, float value)				  override { mFloatOverrides[name] = value;     };
		void SetInt(const std::string& name, int value)					  override { mIntOverrides[name] = value;       };
		void SetVec2(const std::string& name, const Vector2& value)		  override { mVec2Overrides[name] = value;      };
		void SetVec3(const std::string& name, const Vector3& value)		  override { mVec3Overrides[name] = value;      };
		void SetVec4(const std::string& name, const Vector4& value)		  override { mVec4Overrides[name] = value;      };
		void SetColor(const std::string& name, const Color& value)		  override { mColorOverrides[name] = value;     };
		void SetTexture(const std::string& name, Texture* texture)		  override { mTextureOverrides[name] = texture; };
		void SetMat2(const std::string& name, const glm::mat2& value)	  override { mMat2Uniforms[name] = value;		};
		void SetMat3(const std::string& name, const glm::mat3& value)	  override { mMat3Uniforms[name] = value;       };
		void SetMat4(const std::string& name, const Matrix4& value)		  override { mMat4Uniforms[name] = value;       };
		void SetMat4Row(const std::string& name, const Matrix4Row& value) override { mMat4RowUniforms[name] = value;    };

		void Apply() override;
	};
}
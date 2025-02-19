#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/AssetsType/Texture.h>
#include <Graphics/Shader.h>
#include <vector>
#include <glm/mat4x4.hpp>

namespace clt
{
	class CLUTTER_API SpriteBatch
	{
		Texture* mTexture;
		GLuint mVAO, mVBO;
		std::vector<glm::mat4> mTransform;

	public:
		SpriteBatch(Texture* texture);
		~SpriteBatch();

		void AddSprite(const glm::mat4& pTransform);
		void Draw(Shader& shader);
	};
}
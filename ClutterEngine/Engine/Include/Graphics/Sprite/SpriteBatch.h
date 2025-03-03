#pragma once
#include <Core/CCommon.h>
#include <Core/Assets/AssetsType/Texture.h>
#include <Graphics/Shader/Shader.h>
#include <Graphics/Shader/VertexArray.h>
#include <vector>
#include <glm/mat4x4.hpp>

namespace clt
{
	class SpriteComponent;
	class CLUTTER_API SpriteBatch
	{
		Texture& mTexture;
		VertexArray* mVAO;
		std::vector<SpriteComponent*> mComponents;

	public:
		SpriteBatch(Texture& texture);
		~SpriteBatch();

		void AddSprite(SpriteComponent* comp);
		void RemoveSprite(SpriteComponent* comp);
		void Draw(Shader& pShader);
		void EndDraw();
	};
}
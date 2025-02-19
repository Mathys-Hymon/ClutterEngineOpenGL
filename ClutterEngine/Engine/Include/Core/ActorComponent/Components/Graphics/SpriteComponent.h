#pragma once
#include <Core/ActorComponent/Components/GraphicComponent.h>
#include <Core/Assets/AssetsType/Texture.h>
#include <glm/gtc/matrix_transform.hpp>

namespace clt
{
	class CLUTTER_API SpriteComponent : public GraphicComponent
	{
	protected:
		int mTexWidth, mTexHeight;
		Texture& mTexture;

	public:
		SpriteComponent(Texture& pTexture, int DrawOrder = 0);
		SpriteComponent() = delete;
		SpriteComponent(const SpriteComponent&) = delete;
		SpriteComponent& operator = (const SpriteComponent&) = delete;

		virtual ~SpriteComponent();

		virtual void SetOwner(Actor* pOwner) override
		{
			mOwner = pOwner;
			pOwner->GetLevel().GetRenderer().AddSpriteComponent(this);

		};

		virtual void Unload() override
		{
			mOwner->GetLevel().GetRenderer().RemoveSpriteComponent(this);
		};

		virtual void SetTexture(const Texture& pTexture);
		virtual void Draw(Renderer& pRenderer) override {};

		int GetTexWidth() const { return mTexWidth; };
		int GetTexHeight() const { return mTexHeight; };
		Texture& GetTexture() const { return mTexture; };
		glm::mat4 GetTransform() const;
	};

}
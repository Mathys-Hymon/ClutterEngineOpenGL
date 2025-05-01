#pragma once
#include <Graphics/UI/WidgetElement.h>

namespace clt
{
	class CLUTTER_API SpriteElement : public WidgetElement
	{
	protected:
		Texture* mTexture;

	public:

		SpriteElement(const std::string textureName, Vector2 size = { 1,1 }, Vector2 position = { 0, 0 }, int ZOrder = 0) : WidgetElement(size, position, ZOrder), mTexture(nullptr)
		{
			mTexture = Assets::Get().GetTexture(textureName);
		}

		SpriteElement(Vector2 size = { 1,1 }, Vector2 position = { 0, 0 }, int ZOrder = 0) : WidgetElement(size, position, ZOrder), mTexture(nullptr)
		{
		}

		SpriteElement(Texture* texture, Vector2 size = { 1,1 }, Vector2 position = { 0, 0 }, int ZOrder = 0) 
			: WidgetElement(size, position, ZOrder), mTexture(nullptr)
		{
			mTexture = texture;
		}
		~SpriteElement() = default;

		virtual Transform2D GetTransform() const override
		{
			return
			{
				mTransform.location,
				mTransform.scale* mTexture->GetSize(),
				mTransform.rotation
			};
		};

		virtual Vector2 GetSize() const override
		{
			return mTransform.scale * mTexture->GetSize();
		}

		virtual void Update() override {};

		virtual void Draw(RendererGL* renderer) override
		{
			if (!mTexture) return;
			mTexture->Bind();
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}

		void SetTexture(Texture* pTexture)
		{
			mTexture = pTexture;
		}

		void SetTexture(std::string pTexture)
		{
			mTexture = Assets::Get().GetTexture(pTexture);
		}

		Texture* GetTexture() const { return mTexture; }
	};
}
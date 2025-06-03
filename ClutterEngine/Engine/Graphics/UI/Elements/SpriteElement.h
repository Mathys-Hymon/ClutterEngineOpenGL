#pragma once
#include <Graphics/UI/WidgetElement.h>

namespace clt
{
	/**
  * @brief UI element for rendering a textured sprite.
  * 
  * SpriteElement is a widget that displays a 2D texture. It supports setting the texture
  * by name or pointer, and provides transform and size information based on the texture.
  */
	class CLUTTER_API SpriteElement : public WidgetElement
	{
	protected:
		/**
   * @brief Pointer to the texture used by this sprite.
   */
		Texture* mTexture;

	public:

		/**
   * @brief Construct a SpriteElement with a texture name.
   * @param textureName Name of the texture to use.
   * @param size Size of the sprite (default: {1,1}).
   * @param position Position of the sprite (default: {0,0}).
   * @param ZOrder Z-order for rendering (default: 0).
   */
		SpriteElement(const std::string textureName, Vector2 size = { 1,1 }, Vector2 position = { 0, 0 }, int ZOrder = 0) : WidgetElement(size, position, ZOrder), mTexture(nullptr)
		{
			mTexture = Assets::Get().GetTexture(textureName);
		}

		/**
   * @brief Construct a SpriteElement without a texture.
   * @param size Size of the sprite (default: {1,1}).
   * @param position Position of the sprite (default: {0,0}).
   * @param ZOrder Z-order for rendering (default: 0).
   */
		SpriteElement(Vector2 size = { 1,1 }, Vector2 position = { 0, 0 }, int ZOrder = 0) : WidgetElement(size, position, ZOrder), mTexture(nullptr)
		{
		}

		/**
   * @brief Construct a SpriteElement with a texture pointer.
   * @param texture Pointer to the texture to use.
   * @param size Size of the sprite (default: {1,1}).
   * @param position Position of the sprite (default: {0,0}).
   * @param ZOrder Z-order for rendering (default: 0).
   */
		SpriteElement(Texture* texture, Vector2 size = { 1,1 }, Vector2 position = { 0, 0 }, int ZOrder = 0) 
			: WidgetElement(size, position, ZOrder), mTexture(nullptr)
		{
			mTexture = texture;
		}

		/**
   * @brief Destructor.
   */
		~SpriteElement() = default;

		/**
   * @brief Get the transform of the sprite, including location, scaled size, and rotation.
   * @return Transform2D The current transform.
   */
		virtual Transform2D GetTransform() const override
		{
			return
			{
				mTransform.location,
				mTransform.scale * mTexture->GetSize(),
				mTransform.rotation
			};
		};

		/**
   * @brief Get the size of the sprite, accounting for scale and texture size.
   * @return Vector2 The current size.
   */
		virtual Vector2 GetSize() const override
		{
			return mTransform.scale * mTexture->GetSize();
		}

		/**
   * @brief Update the sprite element. (No-op for SpriteElement.)
   */
		virtual void Update() override {};

		/**
   * @brief Draw the sprite using the provided renderer.
   * @param renderer Pointer to the OpenGL renderer.
   */
		virtual void Draw(RendererGL* renderer) override
		{
			if (!mTexture) return;
			mTexture->Bind();
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}

		/**
   * @brief Set the texture by pointer.
   * @param pTexture Pointer to the new texture.
   */
		void SetTexture(Texture* pTexture)
		{
			mTexture = pTexture;
		}

		/**
   * @brief Set the texture by name.
   * @param pTexture Name of the new texture.
   */
		void SetTexture(std::string pTexture)
		{
			mTexture = Assets::Get().GetTexture(pTexture);
		}

		/**
   * @brief Get the current texture pointer.
   * @return Texture* Pointer to the current texture.
   */
		Texture* GetTexture() const { return mTexture; }
	};
}

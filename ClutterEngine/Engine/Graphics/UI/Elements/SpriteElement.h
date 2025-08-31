#pragma once  
#include <Graphics/UI/WidgetElement.h>  

namespace clt  
{  
class CLUTTER_API SpriteElement : public WidgetElement  
{  
protected:  
	std::weak_ptr<Texture> mTexture;  

public:  

	SpriteElement(const std::string textureName, Vector2 size = { 1,1 }, Vector2 position = { 0, 0 }, int ZOrder = 0) : WidgetElement(size, position, ZOrder)  
	{  
		mTexture = Assets::Get().GetTexture(textureName);  
	}  

	SpriteElement(Vector2 size = { 1,1 }, Vector2 position = { 0, 0 }, int ZOrder = 0) : WidgetElement(size, position, ZOrder)  
	{  
	}  

	SpriteElement(std::shared_ptr<Texture> texture, Vector2 size = { 1,1 }, Vector2 position = { 0, 0 }, int ZOrder = 0)  
		: WidgetElement(size, position, ZOrder)  
	{  
		mTexture = texture;  
	}  
	~SpriteElement() = default;  

	virtual Transform2D GetTransform() const override  
	{  
		return  
		{  
			mTransform.location,  
			mTransform.scale * (mTexture.lock() ? mTexture.lock()->GetSize() : Vector2{1, 1}),  
			mTransform.rotation  
		};  
	};  

	virtual Vector2 GetSize() const override  
	{  
		return mTransform.scale * (mTexture.lock() ? mTexture.lock()->GetSize() : Vector2{1, 1});  
	}  

	virtual void Update() override {};  

	virtual void Draw(RendererGL* renderer) override  
	{  
		auto texture = mTexture.lock();  
		if (!texture) return;  
		texture->Bind();  
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);  
	}  

	void SetTexture(std::weak_ptr<Texture> pTexture)
	{  
		mTexture = pTexture;
	}  

	void SetTexture(std::string pTexture)  
	{  
		mTexture = Assets::Get().GetTexture(pTexture);  
	}  

	Texture& GetTexture() const  
	{  
		auto texture = mTexture.lock();  
		if (!texture)  
			throw std::runtime_error("Texture is no longer available.");  
		return *texture;  
	}  
};  
}
#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Transforms/Transform2D.h>
#include <Core/Assets/AssetsType/Texture.h>
#include <Core/Assets/Assets.h>
#include <Graphics/UI/UIPanel.h>

namespace clt
{
	class CLUTTER_API WidgetElement
	{
		int mZOrder;
		UIPanel* mOwner;

		Transform2D mTransform;

		Texture* mTexture;

		void SetOwner(UIPanel* pOwner) { mOwner = pOwner; };

		friend UIPanel;
	public:

		bool mVisibility;

		WidgetElement() = delete;

		WidgetElement(const std::string textureName, Vector2 size = { 1,1 }, Vector2 position = { 0, 0 }, int ZOrder = 0) : mZOrder(ZOrder), mVisibility(true), mOwner(nullptr), mTexture(nullptr)
		{
			mTexture = Assets::Get().GetTexture(textureName);

			mTransform.scale.x =  size.x;
			mTransform.scale.y = -size.y;

			mTransform.location = position;
		};

		WidgetElement(Texture* texture, Vector2 size = { 1,1 }, Vector2 position = { 0, 0 }, int ZOrder = 0) : mZOrder(ZOrder), mVisibility(true), mOwner(nullptr), mTexture(texture)
		{
			mTransform.scale.x =  size.x;
			mTransform.scale.y = -size.y;

			mTransform.location = position;

			mTexture = texture;
		};

		~WidgetElement() = default;

		virtual void Update() {};

		int GetZOrder() const { return mZOrder; };
		void SetZOrder(int ZOrder)
		{
			if (ZOrder != mZOrder)
			{
				mZOrder = ZOrder;
				mOwner->UpdateWidgetOrder(this);
			}
		}

		Vector2 GetSize()     const 
		{ 
			return {
				 mTransform.scale.x,
				-mTransform.scale.y
					};
		
		};
		Vector2 GetPosition() const { return mTransform.location; };
		float GetRotation()   const { return mTransform.rotation; };

		Transform2D GetTransform() const 
		{
			return { mTransform.location,
					 mTransform.scale * mTexture->GetSize(),
					 mTransform.rotation
			};
		};

		void SetTexture(Texture* pTexture) 
		{ 
			mTexture = pTexture;
		}

		void SetTexture(std::string pTexture) 
		{ 
			mTexture = Assets::Get().GetTexture(pTexture);
		}
		
		Texture* GetTexture() const { return mTexture; }

		void SetSize(Vector2 size) 
		{ 
			mTransform.scale.x =  size.x;
			mTransform.scale.y = -size.y;
		};

		void SetSize(float size)
		{
			mTransform.scale.x = size;
			mTransform.scale.y = -size;
		};

		void SetPosition(Vector2 position) { mTransform.location = position; };

		void SetRotation(float rotation)   { mTransform.rotation = rotation; };

		void ToggleVisibility() { mVisibility = !mVisibility; };
	};
}
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

		WidgetElement(const std::string textureName, Vector2 size = { 25,25 }, Vector2 position = { 0, 0 }, int ZOrder = 0) : mZOrder(ZOrder), mVisibility(true), mOwner(nullptr), mTexture(nullptr)
		{
			mTransform.scale = size;
			mTransform.location = position;

			mTexture = Assets::Get().GetTexture("textureName");
		};

		WidgetElement(Texture* texture, Vector2 size = { 25,25 }, Vector2 position = { 0, 0 }, int ZOrder = 0) : mZOrder(ZOrder), mVisibility(true), mOwner(nullptr), mTexture(nullptr)
		{
			mTransform.scale = size;
			mTransform.location = position;

			mTexture = texture;
		};

		~WidgetElement() = default;

		virtual void Update() = 0;

		int GetZOrder() const { return mZOrder; };
		void SetZOrder(int ZOrder)
		{
			if (ZOrder != mZOrder)
			{
				mZOrder = ZOrder;
				mOwner->UpdateWidgetOrder(this);
			}
		}

		Vector2 GetSize()     const { return mTransform.scale;    };
		Vector2 GetPosition() const { return mTransform.location; };
		float GetRotation()   const { return mTransform.rotation; };

		Transform2D GetTransform() const { return mTransform; };

		Texture* GetTexture() const { return mTexture; }

		void SetSize(Vector2 size)         { mTransform.scale = size; };

		void SetPosition(Vector2 position) { mTransform.location = position; };

		void SetRotation(float rotation)   { mTransform.rotation = rotation; };

		void ToggleVisibility() { mVisibility = !mVisibility; };
	};
}
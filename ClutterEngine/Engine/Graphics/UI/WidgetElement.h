#pragma once
#include <Core/CCommon.h>
#include <Core/Maths/Transforms/Transform2D.h>
#include <Core/Assets/AssetsType/Texture.h>
#include <Core/Assets/Assets.h>
#include <Graphics/UI/UIPanel.h>

enum class CLUTTER_API Anchor
{
	Center,
	Top,
	Bottom,

	Left,
	UpLeft,
	BottomLeft,

	Right,
	UpRight,
	BottomRight,

};

namespace clt
{
	class CLUTTER_API WidgetElement
	{
		int mZOrder;

		Vector2 mAnchorOffset;
		UIPanel* mOwner;
		Anchor mAnchor;

	protected:
		Transform2D mTransform;
		void SetOwner(UIPanel* pOwner) { mOwner = pOwner; };

		friend UIPanel;

	public:

		bool mVisibility;

		WidgetElement(Vector2 size = { 1,1 }, Vector2 position = { 0, 0 }, int ZOrder = 0) : mZOrder(ZOrder), mVisibility(true), mOwner(nullptr), mAnchor(Anchor::Center), mAnchorOffset(Vector2::Zero)
		{
			mTransform.scale.x =  size.x;
			mTransform.scale.y = -size.y;

			mTransform.location = position;
		};

		~WidgetElement() = default;

		virtual void Update() {};

		virtual void Draw(RendererGL* renderer) = 0;

		int GetZOrder() const { return mZOrder; };
		void SetZOrder(int ZOrder)
		{
			if (ZOrder != mZOrder)
			{
				mZOrder = ZOrder;
				mOwner->UpdateWidgetOrder(this);
			}
		}

		virtual Vector2 GetSize()     const 
		{ 
			return {
				 mTransform.scale.x,
				-mTransform.scale.y
					};
		
		};
		Vector2 GetPosition() const { return mTransform.location; };
		float GetRotation()   const { return mTransform.rotation; };

		virtual Transform2D GetTransform() const 
		{
			return mTransform;
		};

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

		void SetAnchor(Anchor anchor)
		{

		}

		void SetPosition(Vector2 position) { mTransform.location = position; };

		void SetRotation(float rotation)   { mTransform.rotation = rotation; };

		void ToggleVisibility() { mVisibility = !mVisibility; };
	};
}